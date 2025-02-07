#ifndef MONTECARLO_HPP
#define MONTECARLO_HPP

#include "options/Option.hpp"
#include "models/GlobalModel.hpp"

class MonteCarlo
{
private:
    Option* option;        // Pointer to the option object
    GlobalModel model;     // Model containing market data, parameters, etc.
    int numberSimulations;  // Number of simulations
    double eps;             // Shifting term
    void priceT(double t, PnlMat* past, PnlRng* rng, double& price, double& priceStd); // Method to compute the price
    void deltaT(double t, PnlMat* past, PnlRng* rng, PnlVect* deltas, PnlVect* deltas_std); // Method to compute the Delta

public:
    // Constructor
    MonteCarlo(Option* option, const GlobalModel& model, int numberSimulations, double eps);

    // Method to compute the price and deltas
    void priceAndDelta(double t, PnlMat* past, PnlRng* rng, double& price, double& priceStd, PnlVect* deltas, PnlVect* deltasStd);
    [[nodiscard]] int getTotalNumberOfAssets() const { return model.getTotalNumberOfAssets(); }

    double getForeignRate(int currencyIndex) const { return model.getForeignRate(currencyIndex); }

    [[nodiscard]] ITimeGrid* getMonitoringGrid() const {return option->getMonitoringGrid();}

    [[nodiscard]] std::vector<int> getAssetCurrencyMapping() const { return option->getAssetCurrencyMapping(); }

    [[nodiscard]] int getNumberRiskyAssets() const {return model.getNumberRiskyAssets(); }

    double getDomesticRate() const { return option->getDomesticInterestRate()->getRate(); }
};

#endif // MONTECARLO_HPP
