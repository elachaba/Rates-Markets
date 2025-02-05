//
// Created by Aymane on 05/02/2025.
//

#include "CallCurrency.hpp"

double CallCurrency::payoff(const PnlMat* path) const
{
    double exchangeRate = MGET(path, path->m - 1, 0);
    double maturity = monitoringTimeGrid_->at(monitoringTimeGrid_->len() - 1);

    return std::max(exchangeRate - strikePrice_, 0.0);
}
