// Portfolio.hpp

#ifndef PORTFOLIO_HPP
#define PORTFOLIO_HPP

#include <vector>
#include "Position.hpp"
#include "montecarlo.hpp"
#include "../utils/ITimeGrid.hpp"

class Portfolio
{
private:
    MonteCarlo monteCarlo_;
    ITimeGrid *rebalancingTimeGrid_;
    std::vector<Position> positions_;


public:
    Portfolio(const MonteCarlo &monteCarlo,
              ITimeGrid *rebalancingTimeGrid,
            PnlMat* marketData);

    ~Portfolio() {
        std::cout << "Portfolio destructor called" << std::endl;
    };

    /**
     * @brief Extracts market data for the monitoring dates up to time t
     * @param t Current time
     * @return Matrix containing market data up to time t
     */
    PnlMat* extractPastData(PnlMat* market, int dateInDays, double t) const;

    /**
     * @brief Simulates portfolio rebalancing at specified dates
     * @param marketData Historic prices of all assets
     * @param rng Random number generator
     */
    void simulateRebalancing(PnlMat* marketData, PnlRng* rng);

    // Accessor for the positions
    const std::vector<Position>& getPositions() const { return positions_; }


};

#endif
