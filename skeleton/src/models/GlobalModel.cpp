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

int GlobalModel::getNumberRiskyAssets() const
{
    return riskyAssets_.size();
}


void GlobalModel::simulate(int t, PnlMat* path, const PnlMat* past, PnlRng* rng)
{

    int indexToFill = 0;
    int monitoringLength = monitoringTimeGrid_->len();
    int nbUnderlying = getTotalNumberOfAssets();
    while (indexToFill < monitoringLength && monitoringTimeGrid_->at(indexToFill) <= t) {
        for (int j = 0; j < nbUnderlying; j++) {
            MLET(path, indexToFill, j) = MGET(past, indexToFill, j);
        }
        indexToFill++;
    }

    PnlVect* pastVals = pnl_vect_create(nbUnderlying);

    if (indexToFill != past->m) {   //in case t isn't a monitoring date
        int dt = monitoringTimeGrid_->at(indexToFill) - t;
        pnl_mat_get_row(pastVals, past, past->m); // the values at t
        fill(indexToFill, dt, path, pastVals, rng);
        indexToFill ++;
    }

    for (int i = indexToFill; i < monitoringLength; i++) {
        int dt = monitoringTimeGrid_->at(i) - monitoringTimeGrid_->at(i-1);
        pnl_mat_get_row(pastVals, path, i-1); // the values at t_{i-1}
        fill(indexToFill, dt, path, pastVals, rng);
    }

    pnl_vect_free(&pastVals);


}

void GlobalModel::shiftAsset(int t, PnlMat* path, int asset, double h, PnlMat* shiftedPath)
{
    int nbTimeSteps = monitoringTimeGrid_->len();
    int idx = 0;
    while (idx < nbTimeSteps - 1 && monitoringTimeGrid_->at(idx) < t) {
        idx++;
    }

    for (int i = idx; i < shiftedPath->m; i++)
        MLET(shiftedPath, i, asset) = MGET(path, i, asset) * (1 + h);

}



void GlobalModel::fill(int indexToFill, double dt, PnlMat* path, const PnlVect* pastVals, PnlRng* rng) {
    for (int i = 0; i < getTotalNumberOfAssets(); i++) {
        double newValue;
        PnlVect* gaussianVect = pnl_vect_create(getTotalNumberOfAssets());
        pnl_vect_rng_normal(gaussianVect, gaussianVect->size, rng);
        if (i < riskyAssets_.size()) {
            newValue = riskyAssets_.at(i)->sampleNextValue(GET(pastVals, i), dt, gaussianVect);
        } else {
            newValue = currencies_.at(i-riskyAssets_.size())->sampleNextValue(GET(pastVals, i), dt, gaussianVect);
        }
        MLET(path, indexToFill, i) = newValue;
    }
}
