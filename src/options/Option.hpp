//
// Created by Aymane on 03/02/2025.
//

#ifndef OPTION_HPP
#define OPTION_HPP

#include <vector>
#include "../financial/InterestRateModel.hpp"
#include "../utils/ITimeGrid.hpp"
#include "pnl/pnl_matrix.h"

/**
 * @brief Abstract base class representing a financial option.
 */
class Option {
protected:
    std::vector<int> assetCurrencyMapping_; ///< Mapping of assets to their respective currencies.
    std::vector<InterestRateModel*> foreignInterestRates_; ///< Foreign interest rate models for currencies.
    InterestRateModel* domesticInterestRate_; ///< Domestic interest rate model.
    ITimeGrid* monitoringTimeGrid_; ///< Time grid for monitoring the option.

public:
    /**
     * @brief Constructor for the Option class.
     * @param assetCurrencyMapping Mapping of assets to their respective currencies.
     * @param foreignInterestRates Foreign interest rate models.
     * @param domesticInterestRate Domestic interest rate model.
     * @param monitoringTimeGrid Time grid for monitoring the option.
     */
    Option(const std::vector<int>& assetCurrencyMapping,
           const std::vector<InterestRateModel*>& foreignInterestRates,
           InterestRateModel* domesticInterestRate,
           ITimeGrid* monitoringTimeGrid);


    virtual ~Option();

    /**
     * @brief Pure virtual method to calculate the option's payoff.
     * @param path Matrix of asset prices at monitoring dates
     * @return The payoff value as a double.
     */
    virtual double payoff(const PnlMat* path) const = 0;

    // Getters
    const std::vector<int>& getAssetCurrencyMapping() const { return assetCurrencyMapping_; }
    const std::vector<InterestRateModel*>& getForeignInterestRates() const { return foreignInterestRates_; }
    InterestRateModel* getDomesticInterestRate() const { return domesticInterestRate_; }
    ITimeGrid* getMonitoringGrid() const { return monitoringTimeGrid_; }

};

#endif // OPTION_HPP