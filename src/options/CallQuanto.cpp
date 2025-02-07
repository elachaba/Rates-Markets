//
// Created by ASUS on 05/02/2025.
//

#include "CallQuanto.hpp"

double CallQuanto::payoff(const PnlMat* path) const
{
    double foreignAssetPrice = MGET(path, path->m - 1, 0);

    return std::max(foreignAssetPrice - strikePrice_, 0.0);
}
