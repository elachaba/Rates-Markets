//
// Created by Aymane on 03/02/2025.
//

#include "Currency.hpp"

/**
 * @brief Constructor for the Currency class.
 * @param drift The drift term in the stochastic differential equation.
 * @param volatilityVector The volatility vector for stochastic behavior.
 * @param foreignRate The foreign interest rate for the currency.
 * @param domesticRate The domestic interest rate for the currency.
 */
Currency::Currency(double drift, PnlVect* volatilityVector, double foreignRate, double domesticRate)
    : RiskyDynamics(drift, volatilityVector),
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
 * @brief Calculate the discount factor for the foreign interest rate.
 * @param t1 Start time.
 * @param t2 End time.
 * @return Discount factor for the foreign rate.
 */
double Currency::discountForeign(double t1, double t2) const {
    return foreignInterestRate_.discount(t1, t2);
}

/**
 * @brief Calculate the discount factor for the domestic interest rate.
 * @param t1 Start time.
 * @param t2 End time.
 * @return Discount factor for the domestic rate.
 */
double Currency::discountDomestic(double t1, double t2) const {
    return domesticInterestRate_.discount(t1, t2);
}

/**
 * @brief Calculate the capitalization factor for the foreign interest rate.
 * @param t1 Start time.
 * @param t2 End time.
 * @return Capitalization factor for the foreign rate.
 */
double Currency::accountForeign(double t1, double t2) const {
    return foreignInterestRate_.account(t1, t2);
}

/**
 * @brief Calculate the capitalization factor for the domestic interest rate.
 * @param t1 Start time.
 * @param t2 End time.
 * @return Capitalization factor for the domestic rate.
 */
double Currency::accountDomestic(double t1, double t2) const {
    return domesticInterestRate_.account(t1, t2);
}
