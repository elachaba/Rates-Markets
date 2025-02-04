#ifndef CURRENCY_HPP
#define CURRENCY_HPP

#include "financial/InterestRateModel.hpp"
#include "models/RiskyDynamics.hpp"

/**
 * @brief Represents a currency with stochastic dynamics (multi- or single-factor)
 *        and associated interest rate models.
 */
class Currency : public RiskyDynamics {
private:
    InterestRateModel foreignInterestRate_;  ///< Foreign interest rate model
    InterestRateModel domesticInterestRate_; ///< Domestic interest rate model

public:
    /**
     * @brief Constructor for the Currency class.
     * @param drift           The drift term in the SDE.
     * @param volatilityVector The volatility vector for stochastic behavior (could be 1D or more).
     * @param foreignRate     The foreign interest rate for this currency.
     * @param domesticRate    The domestic/base interest rate for this currency.
     */
    Currency(double drift,
             PnlVect* volatilityVector,
             double foreignRate,
             double domesticRate);

    /**
     * @brief Destructor (no special cleanup; base class frees volatility vector).
     */
    ~Currency() override = default;

    /**
     * @brief Get the foreign interest rate.
     */
    double getForeignRate() const;

    /**
     * @brief Get the domestic interest rate.
     */
    double getDomesticRate() const;

    /**
     * @brief Discount factor for the foreign interest rate.
     */
    double discountForeign(double t1, double t2) const;

    /**
     * @brief Discount factor for the domestic interest rate.
     */
    double discountDomestic(double t1, double t2) const;

    /**
     * @brief Capitalization factor for the foreign interest rate.
     */
    double accountForeign(double t1, double t2) const;

    /**
     * @brief Capitalization factor for the domestic interest rate.
     */
    double accountDomestic(double t1, double t2) const;
};

#endif // CURRENCY_HPP
