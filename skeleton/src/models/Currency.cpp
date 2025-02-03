//
// Created by Aymane on 03/02/2025.
//

#include "Currency.hpp"

/**
 * @brief Constructor for the Currency class.
 * @param drift The drift term in the stochastic differential equation.
 * @param volatility The volatility for stochastic behavior.
 * @param foreignRate The foreign interest rate for the currency.
 * @param domesticRate The domestic interest rate for the currency.
 */
Currency::Currency(double drift, double volatility, double foreignRate, double domesticRate)
    : RiskyDynamics(drift, nullptr), // No longer passing a volatility vector
      volatility_(volatility),
      foreignInterestRate_(foreignRate),
      domesticInterestRate_(domesticRate) {}

/**
 * @brief Get the foreign interest rate.
 * @return The foreign interest rate.
 */
double Currency::getForeignRate() const {
    return foreignInterestRate_.getRate();
}

/**
 * @brief Get the domestic interest rate.
 * @return The domestic interest rate.
 */
double Currency::getDomesticRate() const {
    return domesticInterestRate_.getRate();
}

/**
 * @brief Get the volatility of the currency.
 * @return The volatility as a scalar.
 */
double Currency::getVolatility() const {
    return volatility_;
}

/**
 * @brief Calculate the discount factor for the foreign interest rate.
 * @param t1 Start time.
 * @param t2 End time.
 * @return Discount factor for the foreign rate.
 */
double Currency::discountForeign(double t1, double t2) const {
    return foreignInterestRate_.discount(t1, t2);
}

/**
* @brief Calculate the discount facto
