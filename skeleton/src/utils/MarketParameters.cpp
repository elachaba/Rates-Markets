//
// Created by Aymane on 06/02/2025.
//
#include "json_reader.hpp"
#include "MarketParameters.hpp"

MarketParameters MarketParameters::fromJson(const nlohmann::json& j)
{
    MarketParameters marketParams;

    marketParams.domesticCurrencyId = j.at("DomesticCurrencyId").get<std::string>();

    double domesticInterestRate = 0.0;

    for (const auto& currency : j.at("Currencies"))
    {
        if (currency.at("id") == marketParams.domesticCurrencyId)
            domesticInterestRate = currency.at("InterestRate").get<double>();
    }

    for (const auto& currency : j.at("Currencies"))
    {
        CurrencyInfo info{};
        info.id = currency.at("id").get<std::string>();
        info.interestRate = currency.at("InterestRate").get<double>();
        info.volatility = currency.at("Volatility").get<double>();
        if (info.id != marketParams.domesticCurrencyId)
            info.drift = domesticInterestRate;
        else
            info.drift = 0.0;

        marketParams.currencies.push_back(info);
    }

    // Parse assets
    for (const auto& asset : j.at("Assets"))
    {
        AssetInfo info{};
        info.currencyId = asset.at("CurrencyId").get<std::string>();
        info.drift = domesticInterestRate;
        info.volatility = asset.at("Volatility").get<double>();

        marketParams.assets.push_back(info);
    }

    // Parse correlation matrix
    marketParams.correlationMatrix = nullptr;
    j.at("Correlations").get_to(marketParams.correlationMatrix);

    return marketParams;

}

double MarketParameters::getDomesticRate() const
{
    for (const auto& currency : MarketParameters::currencies)
    {
        if (currency.id == domesticCurrencyId)
            return currency.interestRate;
    }
}

MarketParameters::~MarketParameters()
{
    if (correlationMatrix)
    {
        pnl_mat_free(&correlationMatrix);
        correlationMatrix = nullptr;
    }
}

