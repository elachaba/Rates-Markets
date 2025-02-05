//
// Created by Aymane on 05/02/2025.
//

#include "QuantoExchange.hpp"

double QuantoExchange::payoff(const PnlMat* path) const
{
    double domesticAssetPrice = MGET(path, path->m - 1, 0);
    double foreignAssetPrice = MGET(path, path->m - 1, 1);

    return std::max(domesticAssetPrice - foreignAssetPrice - strikePrice_, 0.0);
}
