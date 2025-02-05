//
// Created by Aymane on 03/02/2025.
//

#include "RiskyDynamics.hpp"

#include <stdexcept>
#include <valarray>
#include <pnl/pnl_vector.h>

RiskyDynamics::RiskyDynamics(double drift, PnlVect* volatilityVector) : drift_(drift)
{
    if (volatilityVector == nullptr)
        throw std::runtime_error("Volatility vector cannot be null");

    volatilityVector_ = pnl_vect_copy(volatilityVector);
}

RiskyDynamics::~RiskyDynamics()
{
    pnl_vect_free(&volatilityVector_);
}

double RiskyDynamics::sampleNextValue(double currentValue, double dt, PnlVect* gaussianVect) const
{
    // Implementation of the log-normal dynamics:
    // S(t+dt) = S(t) * exp((drift - 0.5*σ²)dt + σ*dW)

    double volSquared = pnl_vect_scalar_prod(volatilityVector_, volatilityVector_);

    double driftTerm = (drift_ - 0.5 * volSquared) * dt;
    double diffusionTerm = std::sqrt(dt) * pnl_vect_scalar_prod(volatilityVector_, gaussianVect);

    return currentValue * std::exp(driftTerm + diffusionTerm);
}

int RiskyDynamics::size() const
{
    return volatilityVector_->size;
}

double RiskyDynamics::getDrift() const
{
    return drift_;
}




