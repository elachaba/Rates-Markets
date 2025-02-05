//
// Created by Aymane on 04/02/2025.
//

#ifndef GLOBALMODELBUILDER_HPP
#define GLOBALMODELBUILDER_HPP

#include <nlohmann/json.hpp>
#include "models/GlobalModel.hpp"
#include "pnl/pnl_matrix.h"
#include <utility>

class GlobalModelBuilder {
public:
    static GlobalModel* createFromJson(const nlohmann::json& params);

private:
    static std::pair<std::string, double> parseDomesticCurrency(const nlohmann::json& params);
    static PnlMat* createCholeskyMatrix(const nlohmann::json& params);

    static std::vector<RiskyAsset*> createRiskyAssets(const nlohmann::json& params,
                                                     const PnlMat* choleskyMatrix,
                                                     double domesticRate,
                                                     int& currentIndex);

    static std::vector<Currency*> createCurrencies(const nlohmann::json& params,
                                                 const PnlMat* choleskyMatrix,
                                                 const std::string& domesticCurrencyId,
                                                 double domesticRate,
                                                 int& currentIndex);

    static ITimeGrid* createTimeGrid(const nlohmann::json& params);
};


#endif //GLOBALMODELBUILDER_HPP
