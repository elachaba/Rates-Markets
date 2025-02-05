//
// Created by Aymane on 05/02/2025.
//

#include "CallCurrency.hpp"

double CallCurrency::payoff(const PnlMat* path) const
{
    double exchangeRate = MGET(path, path->m - 1, 0);
    double maturity = monitoringTimeGrid_->at(monitoringTimeGrid_->len() - 1);
    double accountFactor = foreignInterestRates_[0]->account(0.0, maturity);

    return std::max(exchangeRate * accountFactor - strikePrice_, 0.0);
}
