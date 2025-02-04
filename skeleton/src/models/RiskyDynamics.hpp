//
// Created by Aymane on 03/02/2025.
//

#ifndef RISKYDYNAMICS_HPP
#define RISKYDYNAMICS_HPP
#include <pnl/pnl_vector.h>


class RiskyDynamics {
private:
    double drift_;
    PnlVect* volatilityVector_;

public:
    RiskyDynamics(double drift, PnlVect* volatilityVector);

    virtual ~RiskyDynamics();

    /**
     * @brief Sample the next value using the SDE
     * @param currentValue Current asset/FX value
     * @param dt Time step
     * @param brownian Brownian increment
     * @return Next value
     */
    double sampleNextValue(double currentValue, double dt, double brownian) const;

    /**
     * @brief Get the size of the volatility vector
     */

    int size() const;

    double getDrift() const;

    // TODO: remove (for testing purposes)
    PnlVect* getVolatility() const { return volatilityVector_; }

};



#endif //RISKYDYNAMICS_HPP
