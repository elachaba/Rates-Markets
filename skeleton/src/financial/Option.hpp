//
// Created by Aymane on 03/02/2025.
//

#ifndef OPTION_HPP
#define OPTION_HPP

#include <vector>
#include "InterestRateModel.hpp"
#include "utils/TimeGrid.hpp"

/**
 * @brief Abstract base class representing a financial option.
 */
class Option {
protected:
    std::vector<int> assetCurrencyMapping; ///< Mapping of assets to their respective currencies.
    std::vector<InterestRateModel> foreignInterestRates; ///< Foreign interest rate models for currencies.
    InterestRateModel domesticInterestRate; ///< Domestic interest rate model.
    TimeGrid monitoringTimeGrid; ///< Time grid for monitoring the option.

public:
    /**
     * @brief Constructor for the Option class.
     * @param assetCurrencyMapping Mapping of assets to their respective currencies.
     * @param foreignInterestRates Foreign interest rate models.
     * @param domesticInterestRate Domestic interest rate model.
     * @param monitoringTimeGrid Time grid for monitoring the option.
     */
    Option(const std::vector<int>& assetCurrencyMapping,
           const std::vector<InterestRateModel>& foreignInterestRates,
           const InterestRateModel& domesticInterestRate,
           const TimeGrid& monitoringTimeGrid);

    /**
     * @brief Virtual destructor to allow cleanup in derived classes.
     */
    virtual ~Option() = default;

    /**
     * @brief Pure virtual method to calculate the option's payoff.
     * @return The payoff value as a double.
     */
    virtual double payoff() const = 0;
};

#endif // OPTION_HPP
