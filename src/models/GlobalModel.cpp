//
// Created by Aymane on 03/02/2025.
//

#include "GlobalModel.hpp"
#include "../utils/json_reader.hpp"


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
    std::cout<<"GlobalModel::~GlobalModel()"<<std::endl;
    if (!riskyAssets_.empty()) {
        for (auto* asset : riskyAssets_) {
            if (asset != nullptr) {
                delete asset;
            }
        }
        riskyAssets_.clear();
    }

    if (!currencies_.empty()) {
        for (auto* currency : currencies_) {
            if (currency != nullptr) {
                delete currency;
            }
        }
        currencies_.clear();
    }

    if (monitoringTimeGrid_ != nullptr) {
        delete monitoringTimeGrid_;
        monitoringTimeGrid_ = nullptr;
    }

    if (domesticInterestRate_ != nullptr) {
        delete domesticInterestRate_;
        domesticInterestRate_ = nullptr;
    }
}

int GlobalModel::getTotalNumberOfAssets() const
{
    return riskyAssets_.size() + currencies_.size();
}

int GlobalModel::getNumberRiskyAssets() const
{
    return riskyAssets_.size();
}


void GlobalModel::simulate(double t, PnlMat* path, const PnlMat* past, PnlRng* rng)
{
    int nbTimeSteps = monitoringTimeGrid_->len();
    int totalNumberOfAssets = getTotalNumberOfAssets();
    int daysInYear = monitoringTimeGrid_->getNumberOfDaysInYear();

    int tDays = static_cast<int> (t * daysInYear);

    int currentIndex = 0;
    while (currentIndex < nbTimeSteps && monitoringTimeGrid_->at(currentIndex) <= tDays)
    {
        for (int j = 0; j < totalNumberOfAssets; j++)
            MLET(path, currentIndex, j) = MGET(past, currentIndex, j);
        currentIndex++;
    }

    // if we have more dates to simulate
    if (currentIndex < nbTimeSteps)
    {
        // Get Last known values from past
        PnlVect* prevValues = pnl_vect_create(totalNumberOfAssets);
        pnl_mat_get_row(prevValues, past, past->m - 1);

        double dt;
        if (t > 0)
            dt = (monitoringTimeGrid_->at(currentIndex) - tDays) / static_cast<double>(daysInYear);
        else
            dt = monitoringTimeGrid_->at(currentIndex) / static_cast<double>(daysInYear);
        fill(currentIndex, dt, path, prevValues, rng);
        currentIndex++;
        pnl_vect_free(&prevValues);

        for (int i = currentIndex; i < nbTimeSteps; i++)
        {
            dt = monitoringTimeGrid_->at(i) - monitoringTimeGrid_->at(i - 1);
            dt /= static_cast<double>(daysInYear);
            prevValues = pnl_vect_create_from_zero(totalNumberOfAssets);
            pnl_mat_get_row(prevValues, path, i - 1);
            fill(i, dt, path, prevValues, rng);
            pnl_vect_free(&prevValues);
        }
    }

}

void GlobalModel::fill(int indexToFill, double dt, PnlMat* path, const PnlVect* pastVals, PnlRng* rng)
{
    PnlVect* gaussianVect = pnl_vect_create(getTotalNumberOfAssets());
    pnl_vect_rng_normal(gaussianVect, gaussianVect->size, rng);

    for (size_t i = 0; i < riskyAssets_.size(); i++)
    {
        double newValue = riskyAssets_[i]->sampleNextValue(GET(pastVals, i), dt, gaussianVect);
        MLET(path, indexToFill, i) = newValue;
    }

    for (size_t i = 0; i < currencies_.size(); i++)
    {
        double newValue = currencies_[i]->sampleNextValue(
            GET(pastVals, riskyAssets_.size() + i),
            dt,
            gaussianVect);
        MLET(path, indexToFill, riskyAssets_.size() + i) = newValue;
    }

    pnl_vect_free(&gaussianVect);
}

void GlobalModel::shiftAsset(double t, PnlMat* path, int asset, double h, PnlMat* shiftedPath)
{
    int nbTimeSteps = monitoringTimeGrid_->len();
    auto daysInYear = (double) monitoringTimeGrid_->getNumberOfDaysInYear();
    int tDays = static_cast<int> (t * daysInYear);

    int idx = 0;
    while (idx < nbTimeSteps - 1 && monitoringTimeGrid_->at(idx) < tDays) {
        idx++;
    }

    for (int i = idx; i < shiftedPath->m; i++)
        MLET(shiftedPath, i, asset) = MGET(path, i, asset) * (1 + h);

}
