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


void GlobalModel::simulate(int t, PnlMat* path, const PnlMat* past, PnlRng* rng)
{
    int i = 0;
    int monitoringLength = monitoringTimeGrid_->len();
    int nbUnderlying = currencies_.size() + riskyAssets_.size(); // to be changed
    while (i < monitoringLength && monitoringTimeGrid_->at(i) <= t) {
        for (int j = 0; j < nbUnderlying; j++) {
            MLET(path, i, j) = MGET(past, i, j);
        }
        i++;
    }

    bool needIntermediateStep = false;

    for (int i = 0; i < nbUnderlying; i++) {

    }



}

void GlobalModel::shiftAsset(int t, PnlMat* path, const PnlMat* past, double h, PnlRng* rng)
{
    // Stub method for shifted path
}