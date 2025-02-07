//
// Created by Aymane on 03/02/2025.
//

#ifndef GLOBALMODEL_HPP
#define GLOBALMODEL_HPP

#include <vector>
#include <pnl/pnl_random.h>
#include <pnl/pnl_matrix.h>
#include "Currency.hpp"
#include "utils/ITimeGrid.hpp"
#include "financial/InterestRateModel.hpp"
#include "financial/RiskyAsset.hpp"


class GlobalModel
{
private:
    std::vector<Currency*> currencies_;
    std::vector<RiskyAsset*> riskyAssets_;
    ITimeGrid* monitoringTimeGrid_;
    InterestRateModel* domesticInterestRate_;

    /**
     * @brief Fill the path matrix at a specific index with simulated values
     * @param indexToFill Index in the path matrix to populate
     * @param dt Time step for simulation
     * @param path Matrix to store the simulated path
     * @param pastVals Last data to use
     * @param rng Random number generator
     */
    void fill(int indexToFill, double dt, PnlMat* path, const PnlVect* pastVals, PnlRng* rng);

public:
    GlobalModel(std::vector<RiskyAsset*> assets,
           std::vector<Currency*> currencies,
           ITimeGrid* timeGrid,
           double domesticRate);

    virtual ~GlobalModel();

    // added them for testing
    [[nodiscard]] const std::vector<RiskyAsset*>& getRiskyAssets() const { return riskyAssets_; }
    [[nodiscard]] const std::vector<Currency*>& getCurrencies() const { return currencies_; }
    [[nodiscard]] const ITimeGrid* getTimeGrid() const { return monitoringTimeGrid_; }
    [[nodiscard]] const InterestRateModel* getInterestRateModel() const { return domesticInterestRate_; }
    [[nodiscard]] int getMaturity() const { return monitoringTimeGrid_->at(monitoringTimeGrid_->len()-1); }


    /**
     * @brief Return the total number assets
     */
    int getTotalNumberOfAssets() const;

    /**
     * @brief Return the total number of risky assets
     */
    int getNumberRiskyAssets() const;

    /**
     * @brief Simulate assets' paths
     * @param t Current time
     * @param path Matrix to store simulated paths
     * @param past Matrix of historic prices
     * @param rng Random number generator
     */
    void simulate(double t, PnlMat* path, const PnlMat* past, PnlRng* rng);

    /**
     * @brief Simulated with shifted asset
     * @param t Current time
     * @param path Matrix to store simulated paths
     * @param h Size of the shift
     * @param asset Index of asset to be shifted
     * @param shiftedPath Shifted path to be filled
     */
    void shiftAsset(double t, PnlMat* path, int asset, double h, PnlMat* shiftedPath);
    double getForeignRate(int currency_index) const { return currencies_[currency_index]->getForeignRate(); };
};

#endif //GLOBALMODEL_HPP
