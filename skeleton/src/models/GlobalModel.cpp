//
// Created by Aymane on 03/02/2025.
//

#include "GlobalModel.hpp"
#include "utils/json_reader.hpp"


GlobalModel::GlobalModel(std::vector<RiskyAsset*> assets,
           std::vector<Currency*> currencies,
           ITimeGrid* timeGrid,
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

int GlobalModel::getTotalNumberOfAssets() const
{
    return riskyAssets_.size() + currencies_.size();
}


void GlobalModel::simulate(int t, PnlMat* path, const PnlMat* past, PnlRng* rng)
{
    int indexToFill = 0;
    int monitoringLength = monitoringTimeGrid_->len();
    int nbUnderlying = getTotalNumberOfAssets(); // to be changed
    while (indexToFill < monitoringLength && monitoringTimeGrid_->at(indexToFill) <= t) {
        for (int j = 0; j < nbUnderlying; j++) {
            MLET(path, indexToFill, j) = MGET(past, indexToFill, j);
        }
        indexToFill++;
    }

    if (indexToFill != past->m) {   //in case t isn't a monitoring date
        int dt = monitoringTimeGrid_->at(indexToFill) - t;
        fill(indexToFill, dt, path, past, rng);
        indexToFill ++;
    }

    for (int i = indexToFill; i < monitoringLength; i++) {
        int dt = monitoringTimeGrid_->at(i) - monitoringTimeGrid_->at(i-1);
        fill(indexToFill, dt, path, past, rng);
    }



}

void GlobalModel::shiftAsset(int t, PnlMat* path, const PnlMat* past, double h, PnlRng* rng)
{
    // Stub method for shifted path
}



void GlobalModel::fill(int indexToFill, double dt, PnlMat* path, const PnlMat* past, PnlRng* rng) {
    for (int i = 0; i < getTotalNumberOfAssets(); i++) {

        double newValue;
        if (i < riskyAssets_.size()) {
            newValue = riskyAssets_.at(i)
        }


    }
}