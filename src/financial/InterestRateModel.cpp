//
// Created by Aymane on 03/02/2025.
//

#include "InterestRateModel.hpp"
#include <cmath>

InterestRateModel::InterestRateModel(double rate) : rate_(rate) {}

double InterestRateModel::getRate() const
{
    return rate_;
}

double InterestRateModel::discount(double t1, double t2) const
{
    return std::exp(-rate_ * (t2 - t1));
}

double InterestRateModel::account(double t1, double t2) const
{
    return std::exp(rate_ * (t2 - t1));
}



