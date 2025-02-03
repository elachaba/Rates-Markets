//
// Created by Aymane on 03/02/2025.
//

#ifndef CURRENCY_HPP
#define CURRENCY_HPP

#include "RiskyDynamics.hpp"
#include "financial/InterestRateModel.hpp"

/**
 * @brief Represents a currency with stochastic dynamics and associated interest rate models.
 */
class Currency : public RiskyDynamics {
private:
    double volatility_; ///< Volatility of the currency as a scalar.
    InterestRateModel foreignInterestRate_; ///< Foreign interest rate model.
    InterestRateModel domesticInterestRate_; ///< Domestic interest rate model.

public:
    /**
     * @brief Constructor for the Currency class.
     * @param drift The drift term in the stochastic differential equation.
     * @param volatility The volatility for stochastic behavior.
     * @param foreignRate The foreign interest rate for the currency.
     * @param domesticRate The domestic interest rate for the currency.
     */
    Currency(double drift, double volatility, double foreignRate, double domesticRate);

    /**
     * @brief Destructor.
     */
    ~Currency() override = default;

    /**
     * @brief Get the foreign interest rate.
     * @return The foreign interest rate.
     */
    double getForeignRate() const;

    /**
     * @brief Get the domestic interest rate.
     * @return The domestic interest rate.
     */
    double getDomesticRate() const;

    /**
     * @brief Get the volatility of the currency.
     * @return The volatility as a scalar.
     */
    double getVolatility() const;

    /**
     * @brief Calculate the discount factor for the foreign interest rate.
     * @param t1 Start time.
     * @param t2 End time.
     * @return Discount factor for the foreign rate.
     */
    double discountForeign(double t1, double t2) const;

    /**
     * @brief Calculate the discount factor for the domestic interest rate.
     * @param t1 Start time.
     * @param t2 End time.
     * @return Discount factor for the domestic rate.
     */
    double discountDomestic(double t1, double t2) const;

    /**
     * @brief Calculate the capitalization factor for the foreign interest rate.
     * @param t1 Start time.
     * @param t2 End time.
     * @return Capitalization factor for the foreign rate.
     */
    double accountForeign(double t1, double t2) const;

    /**
     * @brief Calculate the capitalization factor for the domestic interest rate.
     * @param t1 Start time.
     * @param t2 End time.
     * @return Capitalization factor for the domestic rate.
     */
    double accountDomestic(double t1, double t2) const;
};

#endif // CURRENCY_HPP
