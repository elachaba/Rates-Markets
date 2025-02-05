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
    void price(int t, PnlMat* past, PnlRng* rng, double& price, double& confidence_interval); // Method to compute the price
    void Delta(int t, PnlMat* past, PnlRng* rng, PnlVect* deltas, PnlVect* deltas_std); // Method to compute the Delta

public:
    // Constructor
    MonteCarlo(Option* option, const GlobalModel& model, int numberSimulations, double eps);

    // Method to compute the price and deltas
    void priceAndDelta(int t, PnlMat* past, PnlRng* rng, double& price, double& confidence_interval, double& delta, double& delta_price);
};

#endif // MONTECARLO_HPP
