#include <cmath>
#include "montecarlo.hpp"

// Constructor definition
MonteCarlo::MonteCarlo(Option* option, const GlobalModel& model, int numberSimulations, double eps)
    : option(option), model(model), numberSimulations(numberSimulations), eps(eps)
{
    // Empty constructor body
}

// Stub for priceAndDelta() — no actual logic yet
void MonteCarlo::priceAndDelta(int t, PnlMat* past, PnlRng* rng, double& price, double& confidence_interval, double& delta, double& delta_price)
{
    // TODO: implement pricing and delta computations here
    price(t, past, rng, price, confidence_interval);
    delta(t, past, rng, delta, delta_price);

}


void MonteCarlo::price(int t, PnlMat* past, PnlRng* rng, double& price, double& confidence_interval) {


    double sum = 0.0;
    double squared_sum = 0.0;
    double domesticInterestRate = model.getInterestRateModel()->getRate();
    int n = model.getTotalNumberOfAssets();
    int m = model.getTimeGrid()->len();
    PnlMat* path = pnl_mat_create(m, n);

    for (int i = 0; i < numberSimulations; i ++) {
        model.simulate(t, path, past, rng);
        double payoff = option->payoff(path);
        sum += payoff;
        squared_sum += payoff * payoff;
    }

    sum *= model.getInterestRateModel()->discount(t, model.getMaturity());

    price = sum / numberSimulations;
    double variance = squared_sum / numberSimulations - price * price;
    confidence_interval = 1.96 * sqrt(variance / numberSimulations);
    pnl_mat_free(&path);

}


void MonteCarlo::Delta(int t, PnlMat* past, PnlRng* rng, PnlVect* deltas, PnlVect* deltas_std) {

    double diff;
    int nbUnderlying = model.getTotalNumberOfAssets();
    PnlVect* squared_sums = pnl_vect_create(nbUnderlying);

    int m = model.getTimeGrid()->len();
    PnlMat* path = pnl_mat_create(m, nbUnderlying);
    PnlMat* shiftedUp = pnl_mat_create(m, nbUnderlying);
    PnlMat* shiftedDown = pnl_mat_create(m, nbUnderlying);


    for (int m = 0; m < numberSimulations; m++) {
        model.simulate(t, path, past, rng);
        for (int d = 0; d < nbUnderlying; d++) {
            model.shiftAsset(t, path, d, eps, shiftedUp);
            model.shiftAsset(t, path, d, -eps, shiftedDown);
            diff = option->payoff(shiftedUp) - option->payoff(shiftedDown);
            diff *= model.getInterestRateModel()->discount(t, model.getMaturity());
            LET(deltas, d) = GET(deltas, d) + diff;
            LET(squared_sums, d) = GET(squared_sums, d) + diff * diff;
        }
    }


    for (int d = 0; d < nbUnderlying; d++) {
        double s_t = MGET(past, past->m - 1, d); // St is last row in the past
        double mean = GET(deltas, d) / (2.0 * numberSimulations * eps);
        double variance = GET(squared_sums, d) / (4.0 * eps * eps * numberSimulations) - mean * mean;
        LET(deltas, d) = mean / s_t;
        LET(deltas_std, d) = sqrt(variance) / (s_t * sqrt(numberSimulations));
    }

    pnl_mat_free(&shiftedUp);
    pnl_mat_free(&shiftedDown);
    pnl_vect_free(&squared_sums);


}