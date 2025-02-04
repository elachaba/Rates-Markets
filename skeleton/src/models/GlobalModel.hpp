//
// Created by Aymane on 03/02/2025.
//

#ifndef GLOBALMODEL_HPP
#define GLOBALMODEL_HPP

#include <vector>
#include "nlohmann/json.hpp"
#include <pnl/pnl_random.h>
#include "Currency.hpp"
#include "utils/TimeGrid.hpp"
#include "financial/InterestRateModel.hpp"
#include "financial/RiskyAsset.hpp"


class GlobalModel
{
private:
    std::vector<Currency*> currencies_;
    std::vector<RiskyAsset*> riskyAssets_;
    ITimeGrid* monitoringTimeGrid_;
    InterestRateModel* domesticInterestRate_;
    PnlMat* correlationMatrix_;

public:
    GlobalModel(const nlohmann::json& jsonParams);

    virtual ~GlobalModel();

    /**
     * @brief Simulate assets' paths
     * @param t Current time
     * @param path Matrix to store simulated paths
     * @param past Matrix of historic prices
     * @param rng Random number generator
     */
    void simulate(int t, PnlMat* path, const PnlMat* past, PnlRng* rng);

    /**
     * @brief Simulated with shifted asset
     * @param t Current time
     * @param path Matrix to store simulated paths
     * @param past Matrix of the historic prices
     * @param h Size of the shift
     * @rng Random number generator
     */
    void shiftAsset(int t, PnlMat* path, const PnlMat* past, double h, PnlRng* rng);

    /**
     * @brief Initialize the model from JSON parameters
     */

    void initFromJson(const nlohmann::json& jsonParams);
};

#endif //GLOBALMODEL_HPP
