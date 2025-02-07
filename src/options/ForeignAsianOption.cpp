//
// Created by Aymane on 05/02/2025.
//

#include "ForeignAsianOption.hpp"

double ForeignAsianOption::payoff(const PnlMat* path) const
{
    int nbDates = monitoringTimeGrid_->len();
    double sum = 0.0;

    for (int j = 0; j < nbDates; j++)
        sum += MGET(path, j, 1);

    double average = sum / nbDates;
    double domesticAssetPrice = MGET(path, path->m - 1, 0);

    return std::max(average - domesticAssetPrice, 0.0);
}
