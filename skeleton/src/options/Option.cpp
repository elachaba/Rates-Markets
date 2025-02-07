//
// Created by Aymane on 06/02/2025.
//

#include "Option.hpp"

Option::Option(
    const std::vector<int>& assetCurrencyMapping,
    const std::vector<InterestRateModel*>& foreignInterestRates,
    InterestRateModel* domesticInterestRate,
    ITimeGrid* monitoringTimeGrid)
        : assetCurrencyMapping_(assetCurrencyMapping)
        , foreignInterestRates_(foreignInterestRates)
        , domesticInterestRate_(domesticInterestRate)
        , monitoringTimeGrid_(monitoringTimeGrid){}

Option::~Option()
{
    for (auto rate : foreignInterestRates_)
        delete rate;

    delete domesticInterestRate_;
    delete monitoringTimeGrid_;
}
