//
// Created by ASUS on 05/02/2025.
//

#include "CallQuanto.hpp"

double CallQuanto::payoff(const PnlMat* path) const
{
    double foreignAssetPrice = MGET(path, path->m - 1, 0);
    double exchangeRate = MGET(path, path->m - 1, 1);

    return std::max(foreignAssetPrice * exchangeRate - strikePrice_, 0.0);
}
