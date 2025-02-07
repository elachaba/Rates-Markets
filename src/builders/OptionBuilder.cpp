//
// Created by Aymane on 06/02/2025.
//

#include "OptionBuilder.hpp"

#include <nlohmann/json.hpp>

#include "TimeGridBuilder.hpp"
#include "../utils/FinancialInstrumentBuilder.hpp"
#include "../utils/FixedTimeGrid.hpp"
#include "../utils/GridTimeGrid.hpp"
#include "../utils/MarketParameters.hpp"

Option* OptionBuilder::createFromJson(const nlohmann::json& params)
{
    MarketParameters marketParams = MarketParameters::fromJson(params);

    auto assetCurrencyMapping = FinancialInstrumentBuilder::buildAssetCorrelationMapping(marketParams);
    auto [foreignRates, domesticRate] =
        FinancialInstrumentBuilder::buildInterestRateModels(marketParams);

    ITimeGrid* monitoringTimeGrid = TimeGridBuilder::createFromJson(params);

    std::string optionType = params.at("Option").at("Type").get<std::string>();


    if (optionType == "call_quanto")
    {
        double strike = params.at("Option").at("Strike").get<double>();
        return new CallQuanto(assetCurrencyMapping, foreignRates, domesticRate, monitoringTimeGrid, strike);
    }
    if (optionType == "call_currency") {
        double strike = params.at("Option").at("Strike").get<double>();
        return new CallCurrency(assetCurrencyMapping, foreignRates, domesticRate, monitoringTimeGrid, strike);
    }
    if (optionType == "quanto_exchange")
    {
        double strike = params.at("Option").at("Strike").get<double>();
        return new QuantoExchange(assetCurrencyMapping, foreignRates, domesticRate, monitoringTimeGrid, strike);
    }
    if (optionType == "foreign_asian")
        return new ForeignAsianOption(assetCurrencyMapping, foreignRates, domesticRate, monitoringTimeGrid);

    if (optionType == "foreign_perf_basket")
    {
        double strike = params.at("Option").at("Strike").get<double>();
        return new ForeignPerfBasket(assetCurrencyMapping, foreignRates, domesticRate, monitoringTimeGrid, strike);
    }

    // ELSE
    // Clean up and throw error
    delete monitoringTimeGrid;
    for (auto rate : foreignRates)
        delete rate;
    delete domesticRate;

    throw std::runtime_error("OptionBuilder::createFromJson: Unknown option type: " + optionType);
}
