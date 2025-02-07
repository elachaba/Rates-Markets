#include "Currency.hpp"
#include <pnl/pnl_vector.h>

/**
 * @brief Constructor for the Currency class.
 * @param drift            The drift term in the stochastic differential equation.
 * @param volatilityVector The volatility vector for stochastic behavior (one or more dimensions).
 * @param foreignRate      The foreign interest rate for this currency.
 * @param domesticRate     The domestic (base) interest rate for this currency.
 */
Currency::Currency(double drift,
                   PnlVect* volatilityVector,
                   double foreignRate,
                   double domesticRate)
    : RiskyDynamics(drift, volatilityVector),
      foreignInterestRate_(foreignRate),
      domesticInterestRate_(domesticRate)
{
    // The base class (RiskyDynamics) now owns volatilityVector_ and
    // will free it in its destructor. No extra steps needed here.
}

double Currency::getForeignRate() const {
    return foreignInterestRate_.getRate();
}

double Currency::getDomesticRate() const {
    return domesticInterestRate_.getRate();
}

double Currency::discountForeign(double t1, double t2) const {
    return foreignInterestRate_.discount(t1, t2);
}

double Currency::discountDomestic(double t1, double t2) const {
    return domesticInterestRate_.discount(t1, t2);
}

double Currency::accountForeign(double t1, double t2) const {
    return foreignInterestRate_.account(t1, t2);
}

double Currency::accountDomestic(double t1, double t2) const {
    return domesticInterestRate_.account(t1, t2);
}
