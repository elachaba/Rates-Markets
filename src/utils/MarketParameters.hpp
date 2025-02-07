//
// Created by A on 0ymane6/02/2025.
//

#ifndef MARKETPARAMETERS_HPP
#define MARKETPARAMETERS_HPP
#include <optional>
#include <string>
#include <vector>
#include <nlohmann/adl_serializer.hpp>
#include <pnl/pnl_matrix.h>


class MarketParameters {
public:
    struct CurrencyInfo
    {
        std::string id;
        double interestRate;
        double volatility;
        double drift;  // Make drift optional

    };

    struct AssetInfo
    {
        std::string currencyId;
        double drift;
        double volatility;
    };

    std::string domesticCurrencyId;
    std::vector<CurrencyInfo> currencies;
    std::vector<AssetInfo> assets;
    PnlMat* correlationMatrix;

    /**
     * @brief Creates MarketParameters from JSON
     * @param j JSON containing market parameters
     * @return MarketParameters object
     * @throw std::runtime_error if parameters are invalid
     */
    static MarketParameters fromJson(const nlohmann::json& j);


    /**
     * @brief Get domestic interest rate
     * @return Domestic interest rate
     */
    double getDomesticRate() const;

    ~MarketParameters();

};



#endif //MARKETPARAMETERS_HPP
