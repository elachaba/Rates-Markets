//
// Created by Aymane on 05/02/2025.
//

#include "ForeignPerfBasket.hpp"

#include <algorithm>
#include <stdexcept>

double ForeignPerfBasket::payoff(const PnlMat* path) const
{
    if (path->m != 3)
        throw std::invalid_argument("ForeignPerfBasket::payoff: path must have exactly 3 dates for foreign performance basket");

    std::vector<double> performances;
    size_t numAssets = getTotalNumberOfAssets();
    int t3 = 2;

    // Get unique currency IDs (excluding domestic currency 0)
    std::vector<int>currencies = getUniqueCurrencies();

    for (int currencyId : currencies)
    {
        if (currencyId > 0)
        {
            double performance = computeCurrencyPerformance(path, currencyId, numAssets);
            performances.push_back(performance);
        }
    }

    auto maxIt = std::max_element(performances.begin(), performances.end());
    auto imax = std::distance(performances.begin(), maxIt) + 1;

    double foreignAvg = computeBasketAverage(path, t3, imax);
    double domesticAvg = computeBasketAverage(path, t3, 0);

    return std::max(foreignAvg - domesticAvg - strikePrice_, 0.0);

}

double ForeignPerfBasket::computeCurrencyPerformance(const PnlMat* path, int currencyId, int numAssets) const
{
    int t1 = 0, t2 = 1;

    double fxT1 = MGET(path, t1, numAssets + currencyId - 1);
    double fxT2 = MGET(path, t2, numAssets + currencyId - 1);

    double sumT1 = 0.0, sumT2 = 0.0;
    int count = 0;

    for (size_t i = 0; i < assetCurrencyMapping_.size(); i++)
    {
        if (assetCurrencyMapping_.at(i) == currencyId)
        {
            sumT1 += MGET(path, t1, i) / fxT1;
            sumT2 += MGET(path, t2, i) / fxT2;
            count++;
        }
    }

    return count > 0 ? sumT2 / sumT1 : 0.0;
}

double ForeignPerfBasket::computeBasketAverage(const PnlMat* path, int date, size_t currencyId) const
{
    double sum = 0.0;
    int count = 0;

    for (size_t i = 0; i < assetCurrencyMapping_.size(); i++)
    {
        if (assetCurrencyMapping_.at(i) == currencyId)
        {
            sum += MGET(path, date, i);
            count++;
        }
    }

    return count > 0 ? sum / count : 0.0;
}

size_t ForeignPerfBasket::getTotalNumberOfAssets() const
{
    return assetCurrencyMapping_.size();
}

std::vector<int> ForeignPerfBasket::getUniqueCurrencies() const
{
    std::vector<int> currencies = assetCurrencyMapping_;
    std::sort(currencies.begin(), currencies.end());
    currencies.erase(std::unique(currencies.begin(), currencies.end()), currencies.end());

    return currencies;
}


