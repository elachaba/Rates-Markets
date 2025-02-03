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