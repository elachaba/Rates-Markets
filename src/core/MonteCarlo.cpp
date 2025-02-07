#include <cmath>
#include "montecarlo.hpp"

// Constructor definition
MonteCarlo::MonteCarlo(Option* option, const GlobalModel& model, int numberSimulations, double eps)
    : option(option), model(model), numberSimulations(numberSimulations), eps(eps)
{
    // Empty constructor body
}

// Stub for priceAndDelta()
void MonteCarlo::priceAndDelta(double t, PnlMat* past, PnlRng* rng, double& price, double& priceStd, PnlVect* deltas, PnlVect* deltasStd)
{
    // TODO: implement pricing and delta computations here
    priceT(t, past, rng, price, priceStd);
    deltaT(t, past, rng, deltas, deltasStd);

}


void MonteCarlo::priceT(double t, PnlMat* past, PnlRng* rng, double& price, double& priceStd) {


    double sum = 0.0;
    double squared_sum = 0.0;
    int n = model.getTotalNumberOfAssets();
    int m = model.getTimeGrid()->len();
    PnlMat* path = pnl_mat_create(m, n);

    // Scaling time for appropriate discout
    int maturityInDays = model.getMaturity();
    double maturityInYears;
    maturityInYears = (double) maturityInDays / model.getTimeGrid()->getNumberOfDaysInYear();


    double discount_factor = model.getInterestRateModel()->discount(t, maturityInYears);

    for (int i = 0; i < numberSimulations; i ++) {
        model.simulate(t, path, past, rng);
        double payoff = option->payoff(path);
        sum += payoff;
        squared_sum += payoff * payoff;
    }

    double mean = sum / numberSimulations;
    price = mean * discount_factor;

    double variance = discount_factor * discount_factor * (squared_sum / numberSimulations - mean * mean);
    priceStd = sqrt(fabs(variance) / numberSimulations);
    pnl_mat_free(&path);

}


void MonteCarlo::deltaT(double t, PnlMat* past, PnlRng* rng, PnlVect* deltas, PnlVect* deltasStd) {

    double diff, square_sums;
    int nbUnderlying = model.getTotalNumberOfAssets();

    int numberTimeSteps = model.getTimeGrid()->len();
    PnlMat* path = pnl_mat_create(numberTimeSteps, nbUnderlying);
    PnlMat* shiftedUp = pnl_mat_create(numberTimeSteps, nbUnderlying);
    PnlMat* shiftedDown = pnl_mat_create(numberTimeSteps, nbUnderlying);

    // Scaling for appropriate discount
    int maturityInDays = model.getMaturity();
    auto maturityInYears = static_cast<double>(maturityInDays) / model.getTimeGrid()->getNumberOfDaysInYear();

    double discount_factor = model.getInterestRateModel()->discount(t, maturityInYears);


    for (int d = 0; d < nbUnderlying; d++)
    {
        diff = 0.0;
        square_sums = 0.0;
        for (int m = 0; m < numberSimulations; m++)
        {
            model.simulate(t, path, past, rng);
            pnl_mat_clone(shiftedUp, path);
            pnl_mat_clone(shiftedDown, path);
            model.shiftAsset(t, path, d, eps, shiftedUp);
            model.shiftAsset(t, path, d, -eps, shiftedDown);

            double payoffUp = option->payoff(shiftedUp);
            double payoffDown = option->payoff(shiftedDown);

            diff += payoffUp - payoffDown;
            square_sums +=  (payoffUp - payoffDown) * (payoffUp - payoffDown);
        }
        double mean = diff / numberSimulations;
        double variance = discount_factor * discount_factor * (square_sums / numberSimulations - mean * mean);

        double spot = MGET(past, past->m - 1, d);
        double delta = mean * discount_factor / (2.0 * spot * eps) ;
        LET(deltas, d) = delta;
        double deltaStdDev = sqrt(fabs(variance) / numberSimulations) / (2.0 * spot * eps);
        LET(deltasStd, d) = deltaStdDev;
    }

    pnl_mat_free(&shiftedUp);
    pnl_mat_free(&shiftedDown);
    pnl_mat_free(&path);


}