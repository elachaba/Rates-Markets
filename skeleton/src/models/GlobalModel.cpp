//
// Created by Aymane on 03/02/2025.
//

#include "GlobalModel.hpp"
#include "utils/json_reader.hpp"


GlobalModel::GlobalModel(std::vector<RiskyAsset*> assets,
           std::vector<Currency*> currencies,
           TimeGrid* timeGrid,
           double domesticRate) :
    currencies_(std::move(currencies))
    , riskyAssets_(std::move(assets))
    , monitoringTimeGrid_(timeGrid)
    , domesticInterestRate_(new InterestRateModel(domesticRate))
{
}

GlobalModel::~GlobalModel()
{
    for (auto asset : riskyAssets_)
        delete asset;

    for (auto currency : currencies_)
        delete currency;

    delete monitoringTimeGrid_;
    delete domesticInterestRate_;

}

