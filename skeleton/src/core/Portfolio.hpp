// Portfolio.hpp

#ifndef PORTFOLIO_HPP
#define PORTFOLIO_HPP

#include <vector>
#include "Position.hpp"
#include "montecarlo.hpp"
#include "utils/ITimeGrid.hpp"

class Portfolio
{
private:
    MonteCarlo monteCarlo_;
    ITimeGrid *rebalancingTimeGrid_;
    std::vector<Position> positions_;
    PnlMat* marketData_;

public:
    Portfolio(const MonteCarlo &monteCarlo,
              ITimeGrid *rebalancingTimeGrid,
            PnlMat* marketData);

    // Main method to run the rebalancing simulation
    void simulateRebalancing(int nbSamples, PnlRng *rng, double shiftSize);

    // Accessor for the positions
    const std::vector<Position>& getPositions() const { return positions_; }

};

#endif
