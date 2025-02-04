//
// Created by Aymane on 03/02/2025.
//

#include "GlobalModel.hpp"
#include <stdexcept>

GlobalModel::GlobalModel(const nlohmann::json& jsonParams)
{
    initFromJson(jsonParams);
}

GlobalModel::~GlobalModel()
{
    for (auto asset : riskyAssets_)
        delete asset;

    for (auto currency : currencies_)
        delete currency;

    delete monitoringTimeGrid_;
    delete domesticInterestRate_;
    pnl_mat_free(&correlationMatrix_);
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

void GlobalModel::initFromJson(const nlohmann::json& jsonParams)
{
    // Stub method for initializing from JSON
}
