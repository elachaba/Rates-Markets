#include "Portfolio.hpp"

Portfolio::Portfolio(const MonteCarlo &monteCarlo,
                     ITimeGrid *rebalancingTimeGrid,
                     PnlMat* marketData)
    : monteCarlo_(monteCarlo),
      rebalancingTimeGrid_(rebalancingTimeGrid),
      marketData_(marketData)
{
    positions_.reserve(rebalancingTimeGrid_->len());
}

void Portfolio::simulateRebalancing(int nbSamples, PnlRng *rng, double shiftSize)
{
    // Example pseudo-code
    double t0 = rebalancingTimeGrid_->at(0);
    double price, priceStd;
    int numberUnderlying = monteCarlo_.getNumberUnderlying();
    PnlVect *delta = pnl_vect_create_from_zero(numberUnderlying);
    PnlVect *deltaStd = pnl_vect_create_from_zero(numberUnderlying);
    ITimeGrid *monitoringTimeGrid = monteCarlo_.getMonitoringGrid();


    // We'll loop over each date in the time grid
    for (int i = 0; i < rebalancingTimeGrid_->len(); i++)
    {
        int t = rebalancingTimeGrid_->at(i);

        // Step 1: Determine how many rows are needed in "past"
        int index = 0;
        while (index < monitoringTimeGrid->len() && monitoringTimeGrid->at(index) < t) {
            index++;
        }

        // Check if the current index points to a monitoring time exactly equal to t
        if (index < monitoringTimeGrid->len() && monitoringTimeGrid->at(index) == t) {
            index++; // Include this row in "past"
        }

        // Step 2: Create "past" with the exact number of rows needed
        PnlMat *past = pnl_mat_create(index, numberUnderlying);

        // Step 3: Fill "past" with relevant data
        for (int k = 0; k < index; k++) {
            for (int j = 0; j < numberUnderlying; j++) {
                // Copy data from marketData_ to past
                MLET(past, k, j) = MGET(marketData_, monitoringTimeGrid->at(k), j);
            }
        }

        // Proceed to use "past" (no need to resize!)
        monteCarlo_.priceAndDelta(t, past, rng, price, priceStd, delta, deltaStd);


        // 1. Price and delta
        monteCarlo_.priceAndDelta(
            t,
            past,
            rng,
            price,
            priceStd,
            delta,
            deltaStd
        );

        // 2. Build a Position object with the results
        Position pos = Position(t, price, priceStd, delta, deltaStd, 1.0);


        // 4. Store
        positions_.push_back(pos);
    }

}
