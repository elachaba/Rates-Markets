//
// Created by Aymane on 03/02/2025.
//

#include "RiskyAsset.hpp"

/**
 * @brief Constructor for the RiskyAsset class.
 * @param drift The drift term in the stochastic differential equation.
 * @param volatilityVector The volatility vector for stochastic behavior.
 * @param domesticRate The domestic interest rate for the asset.
 */
RiskyAsset::RiskyAsset(std::string currencyId, double drift, PnlVect* volatilityVector, double domesticRate)
    : RiskyDynamics(drift, volatilityVector),
        domesticInterestRate_(domesticRate),
        currencyId(currencyId) {}

/**
 * @brief Get the domestic interest rate.
 * @return The domestic interest rate.
 */
double RiskyAsset::getDomesticRate() const {
    return domesticInterestRate_.getRate();
}

/**
 * @brief Calculate the discount factor for the domestic interest rate.
 * @param t1 Start time.
 * @param t2 End time.
 * @return Discount factor for the domestic rate.
 */
double RiskyAsset::discount(double t1, double t2) const {
    return domesticInterestRate_.discount(t1, t2);
}

/**
 * @brief Calculate the capitalization factor for the domestic interest rate.
 * @param t1 Start time.
 * @param t2 End time.
 * @return Capitalization factor for the domestic rate.
 */
double RiskyAsset::account(double t1, double t2) const {
    return domesticInterestRate_.account(t1, t2);
}