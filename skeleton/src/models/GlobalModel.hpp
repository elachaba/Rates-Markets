//
// Created by Aymane on 03/02/2025.
//

#ifndef GLOBALMODEL_HPP
#define GLOBALMODEL_HPP

#include <vector>
#include <string>
#include <nlohmann/json.hpp>
#include "pnl/pnl_random.h"
#include "Currency.hpp"
#include "utils/TimeGrid.hpp"
#include "financial/InterestRateModel.hpp"
#include "financial/RiskyAsset.hpp"


class GlobalModel {
private:
    std::vector<Currency*> currencies_;
    std::vector<RiskyAsset*> riskyAssets_;
    ITimeGrid* monitoringTimeGrid_;
    InterestRateModel* domesticInterestRate_;
    PnlMat *correlationMatrix_;
    int nbAssets_;
    int nbCurrencies_;
    std::string domesticCurrencyId_;

public:
    GlobalModel(const nlohmann::json& jsonParams);

    virtual ~GlobalModel();

    /**
     * @brief Simulate asset paths
     * @param t Current time
     * @param path Matrix to store simulated paths
     * @param rng Random number generator
     */
    void simulate(double t,  PnlMat* path, PnlRng* rng);

    /**
     * @brief Simulate with shifted asset
     * @param t Current time
     * @param path Matrix to store simulated paths
     * @param assetIndex Index of asset to shift
     * @param h Size of the shift
     * @param rng Random number generator
     */
    void shiftAsset(double t, PnlMat* path, int assetIndex, double h, PnlRng* rng);

    /**
     * @brief Get total number oof assets (including currencies)
     */
    int getTotalSize() const
    {
        return nbAssets_ + nbCurrencies_;
    }

    /**
     * @brief Get the monitoring dates
     */
    const ITimeGrid* getTimeGrid() const
    {
        return monitoringTimeGrid_;
    }

private:
    /**
     * @brief Initialize model from JSON parameters
     */
    void initFromJson(const nlohmann::json& jsonParams);

    /**
     * @brief Apply Cholesky correlation to random vector
     */
    void applyCorrelation(PnlVect* randomVector);
};



#endif //GLOBALMODEL_HPP
