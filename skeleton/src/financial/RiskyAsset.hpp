//
// Created by Aymane on 03/02/2025.
//

#ifndef RISKYASSET_HPP
#define RISKYASSET_HPP

#include "models/RiskyDynamics.hpp"
#include "InterestRateModel.hpp"

/**
 * @brief Represents a risky asset with stochastic dynamics and an associated domestic interest rate model.
 */
class RiskyAsset : public RiskyDynamics {
private:
    InterestRateModel domesticInterestRate_; ///< Domestic interest rate model for the asset.

public:
    /**
     * @brief Constructor for the RiskyAsset class.
     * @param drift The drift term in the stochastic differential equation.
     * @param volatilityVector The volatility vector for stochastic behavior.
     * @param domesticRate The domestic interest rate for the asset.
     */
    RiskyAsset(double drift, PnlVect* volatilityVector, double domesticRate);

    /**
     * @brief Destructor.
     */
    ~RiskyAsset() override = default;

    /**
     * @brief Get the domestic interest rate.
     * @return The domestic interest rate.
     */
    double getDomesticRate() const;

    /**
     * @brief Calculate the discount factor for the domestic interest rate.
     * @param t1 Start time.
     * @param t2 End time.
     * @return Discount factor for the domestic rate.
     */
    double discount(double t1, double t2) const;

    /**
     * @brief Calculate the capitalization factor for the domestic interest rate.
     * @param t1 Start time.
     * @param t2 End time.
     * @return Capitalization factor for the domestic rate.
     */
    double account(double t1, double t2) const;
};

#endif // RISKYASSET_HPP
