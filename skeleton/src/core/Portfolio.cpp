#include "Portfolio.hpp"

Portfolio::Portfolio(const MonteCarlo &monteCarlo,
                     ITimeGrid *rebalancingTimeGrid,
                     PnlMat* marketData)
    : monteCarlo_(monteCarlo),
      rebalancingTimeGrid_(rebalancingTimeGrid)
{
    positions_.reserve(rebalancingTimeGrid_->len());
}

PnlMat* Portfolio::extractPastData(PnlMat* market, int dateInDays, double t) const
{
    ITimeGrid* monitoringGrid = monteCarlo_.getMonitoringGrid();
    int numAssets = monteCarlo_.getTotalNumberOfAssets();
    int numRiskyAssets = monteCarlo_.getNumberRiskyAssets();
    std::vector<int> assetCurrencyMapping = monteCarlo_.getAssetCurrencyMapping();

    // Get all valid dates up to dateInDays
    std::vector<int> validDates;
    for(int i = 0; i < monitoringGrid->len(); i++) {
        int date = monitoringGrid->at(i);
        if(date <= dateInDays) {
            validDates.push_back(date);
        } else {
            break;
        }
    }

    // Add dateInDays if it's not already included
    bool isMonitoringDate = monitoringGrid->has(dateInDays);
    if(!isMonitoringDate) {
        validDates.push_back(dateInDays);
    }

    // Create matrix
    PnlMat* past = pnl_mat_create(validDates.size(), numAssets);

    // Fill matrix using validDates
    for(size_t i = 0; i < validDates.size(); i++) {
        int date = validDates[i];

        for (int j = 0; j < numRiskyAssets; j++) {
            double value = MGET(market, date, j);
            if (assetCurrencyMapping[j] > 0) {
                double fxRate = MGET(market, date, numRiskyAssets + assetCurrencyMapping[j] - 1);
                value *= fxRate;
            }
            MLET(past, i, j) = value;
        }

        for (int j = numRiskyAssets; j < numAssets; j++) {
            double fxRate = MGET(market, date, j);
            int currentIndex = j - numRiskyAssets;
            double foreignRate = monteCarlo_.getForeignRate(currentIndex);
            MLET(past, i, j) = fxRate * exp(foreignRate * t);
        }
    }

    return past;
}

void Portfolio::simulateRebalancing(PnlMat* marketData, PnlRng* rng)
{
    const int numAssets = monteCarlo_.getTotalNumberOfAssets();
    double price = 0, priceStd = 0;
    PnlVect* deltas = pnl_vect_create_from_zero(numAssets);
    PnlVect* deltasStd = pnl_vect_create_from_zero(numAssets);
    auto daysInYear = static_cast<double>(rebalancingTimeGrid_->getNumberOfDaysInYear());

    // First position
    double t = 0.0;
    PnlMat* past = extractPastData(marketData, 0, 0.0);
    monteCarlo_.priceAndDelta(t, past, rng, price, priceStd, deltas, deltasStd);

    // Get initial spots for calculating risky position
    PnlVect* spots = pnl_vect_create(numAssets);
    pnl_mat_get_row(spots, past, past->m - 1);

    // Initial portfolio value equals option price
    double portfolioValue = price;
    // Cash value is portfolio value minus risky position
    double riskyValue = pnl_vect_scalar_prod(deltas, spots);
    double cashValue = portfolioValue - riskyValue;

    Position position(0, price, priceStd, deltas, deltasStd, cashValue, portfolioValue);
    positions_.push_back(position);

    pnl_vect_free(&deltas);
    pnl_vect_free(&deltasStd);

    pnl_vect_free(&spots);
    pnl_mat_free(&past);

    // For subsequent dates
    for (int dateIndex = 1; dateIndex < rebalancingTimeGrid_->len(); dateIndex++)
    {
        deltas = pnl_vect_create_from_zero(numAssets);
        deltasStd = pnl_vect_create_from_zero(numAssets);

        if (!rebalancingTimeGrid_->has(dateIndex))
            continue;

        t = static_cast<double>(rebalancingTimeGrid_->at(dateIndex)) / daysInYear;
        past = extractPastData(marketData, dateIndex, t);

        PnlVect* currentSpots = pnl_vect_create(numAssets);
        pnl_mat_get_row(currentSpots, past, past->m - 1);

        double dt = (rebalancingTimeGrid_->at(dateIndex) - rebalancingTimeGrid_->at(dateIndex - 1)) / daysInYear;

        // Get portfolio value using previous position
        portfolioValue = positions_.back().computeValue(currentSpots, dt, monteCarlo_.getDomesticRate());

        // Calculate new position
        monteCarlo_.priceAndDelta(t, past, rng, price, priceStd, deltas, deltasStd);

        // Calculate new cash value
        riskyValue = pnl_vect_scalar_prod(deltas, currentSpots);
        cashValue = portfolioValue - riskyValue;

        Position newPosition(dateIndex, price, priceStd, deltas, deltasStd, cashValue, portfolioValue);
        positions_.push_back(newPosition);

        pnl_vect_free(&deltas);
        pnl_vect_free(&deltasStd);

        pnl_mat_free(&past);
        pnl_vect_free(&currentSpots);
    }

}