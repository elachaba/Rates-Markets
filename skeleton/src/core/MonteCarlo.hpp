#ifndef MONTECARLO_HPP
#define MONTECARLO_HPP

#include "financial/Option.hpp"
#include "models/GlobalModel.hpp"

class MonteCarlo
{
private:
    Option* option;        // Pointer to the option object
    GlobalModel model;     // Model containing market data, parameters, etc.

public:
    // Constructor
    MonteCarlo(Option* option, const GlobalModel& model);

    // Method to compute the price and deltas (currently no implementation)
    void priceAndDelta();
};

#endif // MONTECARLO_HPP
