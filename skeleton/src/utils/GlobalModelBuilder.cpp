//
// Created by ASUS on 04/02/2025.
//

#include "GlobalModelBuilder.hpp"
#include "json_reader.hpp"
#include <stdexcept>

GlobalModel* GlobalModelBuilder::createFromJson(const nlohmann::json& params) {
    int currentIndex = 0;

    // Parse domestic currency info
    auto [domesticCurrencyId, domesticRate] = parseDomesticCurrency(params);

    // Create correlation/cholesky matrix
    PnlMat* choleskyMatrix = createCholeskyMatrix(params);

    // Create assets and currencies
    auto assets = createRiskyAssets(params, choleskyMatrix, domesticRate, currentIndex);
    auto currencies = createCurrencies(params, choleskyMatrix, domesticCurrencyId, domesticRate, currentIndex);

    // Create time grid
    TimeGrid* timeGrid = createTimeGrid(params);

    // Clean up
    pnl_mat_free(&choleskyMatrix);

    // Create and return model
    return new GlobalModel(assets, currencies, timeGrid, domesticRate);
}

std::pair<std::string, double> GlobalModelBuilder::parseDomesticCurrency(const nlohmann::json& params) {
    std::string domesticCurrencyId = params.at("DomesticCurrencyId").get<std::string>();
    double domesticRate = 0.0;

    auto jsonCurrencies = params.at("Currencies");
    for (const auto& jsonCurrency : jsonCurrencies) {
        if (jsonCurrency.at("id").get<std::string>() == domesticCurrencyId) {
            domesticRate = jsonCurrency.at("InterestRate").get<double>();
            return {domesticCurrencyId, domesticRate};
        }
    }
    throw std::runtime_error("GlobalModelBuilder: Domestic currency not found");
}

PnlMat* GlobalModelBuilder::createCholeskyMatrix(const nlohmann::json& params) {
    PnlMat* correlationMatrix;
    params.at("Correlations").get_to(correlationMatrix);

    PnlMat* choleskyMatrix = pnl_mat_copy(correlationMatrix);
    pnl_mat_free(&correlationMatrix);

    if (pnl_mat_chol(choleskyMatrix) != 0) {
        pnl_mat_free(&choleskyMatrix);
        throw std::runtime_error("GlobalModelBuilder: Cholesky decomposition failed");
    }

    return choleskyMatrix;
}

std::vector<RiskyAsset*> GlobalModelBuilder::createRiskyAssets(
    const nlohmann::json& params, const PnlMat* choleskyMatrix, const double domesticRate, int& currentIndex) {

    std::vector<RiskyAsset*> assets;
    auto jsonAssets = params.at("Assets");

    for (const auto& jsonAsset : jsonAssets) {
        std::string currencyId = jsonAsset.at("CurrencyId").get<std::string>();
        double drift = jsonAsset.at("Drift").get<double>();
        double volatility = jsonAsset.at("Volatility").get<double>();

        PnlVect* volatilityVector = pnl_vect_create(choleskyMatrix->n);
        if (currentIndex >= choleskyMatrix->n) {
            pnl_vect_free(&volatilityVector);
            throw std::runtime_error("GlobalModelBuilder: Size mismatch when initializing risky assets");
        }

        pnl_mat_get_row(volatilityVector, choleskyMatrix, currentIndex++);
        pnl_vect_mult_scalar(volatilityVector, volatility);

        assets.push_back(new RiskyAsset(currencyId, drift, volatilityVector, domesticRate));
        pnl_vect_free(&volatilityVector);
    }

    return assets;
}

std::vector<Currency*> GlobalModelBuilder::createCurrencies(
    const nlohmann::json& params, const PnlMat* choleskyMatrix,
    const std::string& domesticCurrencyId, const double domesticRate, int& currentIndex) {

    std::vector<Currency*> currencies;
    auto jsonCurrencies = params.at("Currencies");

    for (const auto& jsonCurrency : jsonCurrencies) {
        std::string currencyId = jsonCurrency.at("id").get<std::string>();
        if (currencyId == domesticCurrencyId) continue;

        double foreignRate = jsonCurrency.at("InterestRate").get<double>();
        double volatility = jsonCurrency.at("Volatility").get<double>();
        double drift = jsonCurrency.at("Drift").get<double>();

        PnlVect* volatilityVector = pnl_vect_create(choleskyMatrix->n);
        if (currentIndex >= choleskyMatrix->n) {
            pnl_vect_free(&volatilityVector);
            throw std::runtime_error("GlobalModelBuilder: Size mismatch when initializing currencies");
        }

        pnl_mat_get_row(volatilityVector, choleskyMatrix, currentIndex++);
        pnl_vect_mult_scalar(volatilityVector, volatility);

        currencies.push_back(new Currency(drift, volatilityVector, foreignRate, domesticRate));
        pnl_vect_free(&volatilityVector);
    }

    return currencies;
}

TimeGrid* GlobalModelBuilder::createTimeGrid(const nlohmann::json& params) {
    nlohmann::json timeGridJson = params.at("Option").at("FixingDatesInDays").at("DatesInDays");
    return new TimeGrid(timeGridJson);
}
