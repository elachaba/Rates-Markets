//
// Created by Aymane on 04/02/2025.
//

#ifndef GLOBALMODELBUILDER_HPP
#define GLOBALMODELBUILDER_HPP

#include <nlohmann/json.hpp>
#include "../models/GlobalModel.hpp"
#include "pnl/pnl_matrix.h"
#include "../utils/MarketParameters.hpp"

class GlobalModelBuilder {
public:

    /**
     * @brief Creates a GlobalModel from JSON configuration
     * @param params JSON parameters
     * @return Pointer to created GlobalModel
     */
    static GlobalModel* createFromJson(const nlohmann::json& params);

private:

    /**
     * @brief Creates risky assets from market parameters
     * @param params Market parameters
     * @param choleskyMatrix Cholesky decomposition of correlation matrix
     * @param currentIndex Current index in the correlation matrix
     * @return Vector of created risky assets
     */
    static std::vector<RiskyAsset*> createRiskyAssets(const MarketParameters& params,
                                                     const PnlMat* choleskyMatrix,
                                                     int& currentIndex);

    /**
     * @brief Creates currencies from market parameters
     * @param params Market parameters
     * @param choleskyMatrix Cholesky decomposition of correlation matrix
     * @param currentIndex Current index in the correlation matrix
     * @return Vector of created currencies
     */
    static std::vector<Currency*> createCurrencies(const MarketParameters& params,
                                                 const PnlMat* choleskyMatrix,
                                                 int& currentIndex);
};


#endif //GLOBALMODELBUILDER_HPP
