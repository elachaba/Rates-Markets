//
// Created by Aymane on 04/02/2025.
//

#include "GlobalModelBuilder.hpp"

#include "TimeGridBuilder.hpp"
#include "../utils/FinancialInstrumentBuilder.hpp"

GlobalModel* GlobalModelBuilder::createFromJson(const nlohmann::json& params)
{
    MarketParameters marketParams = MarketParameters::fromJson(params);

    PnlMat* cholesky = FinancialInstrumentBuilder::createCholeskyMatrix(
        marketParams.correlationMatrix);

    int currentIndex = 0;
    auto assets = createRiskyAssets(marketParams, cholesky, currentIndex);
    auto currencies = createCurrencies(marketParams, cholesky, currentIndex);

    ITimeGrid* monitoringTimeGrid = TimeGridBuilder::createFromJson(
        params);

    pnl_mat_free(&cholesky);

    return new GlobalModel(assets, currencies, monitoringTimeGrid, marketParams.getDomesticRate());

}

std::vector<RiskyAsset*> GlobalModelBuilder::createRiskyAssets(
        const MarketParameters& params, const PnlMat* choleskyMatrix, int& currentIndex)
{
    std::vector<RiskyAsset*> assets;
    PnlVect* volatilityVector = pnl_vect_create_from_zero(choleskyMatrix->n);
    PnlVect* fxVolVector = pnl_vect_create_from_zero(choleskyMatrix->n);

    for (const auto& asset: params.assets)
    {
        if (currentIndex >= choleskyMatrix->n)
            throw std::runtime_error(
                "GlobalModelBuilder::createRiskyAssets: Size missmatch when initializing risky assets"
                );

        // Get asset's volatility vector
        pnl_mat_get_row(volatilityVector, choleskyMatrix, currentIndex++);
        pnl_vect_mult_scalar(volatilityVector, asset.volatility);

        // If foreign asset, add FX volatility
        if (asset.currencyId != params.domesticCurrencyId) {
            double fxVol = 0.0;
            int fxIndex = 0;

            // Find currency's volatility and index
            for (size_t i = 0; i < params.currencies.size(); i++) {
                const auto& currency = params.currencies[i];
                if (currency.id == asset.currencyId) {
                    fxVol = currency.volatility;
                    fxIndex = params.assets.size() + i - 1;
                    break;
                }
            }

            pnl_mat_get_row(fxVolVector, choleskyMatrix, fxIndex);
            pnl_vect_mult_scalar(fxVolVector, fxVol);
            pnl_vect_plus_vect(volatilityVector, fxVolVector);
        }

        PnlVect* assetVol = pnl_vect_copy(volatilityVector);
        assets.push_back(new RiskyAsset(
            asset.currencyId,
            asset.drift,
            assetVol,
            params.getDomesticRate()
            ));
    }

    pnl_vect_free(&volatilityVector);
    pnl_vect_free(&fxVolVector);
    return assets;
}

std::vector<Currency*> GlobalModelBuilder::createCurrencies(
        const MarketParameters& params, const PnlMat* choleskyMatrix, int& currentIndex)
{
    std::vector<Currency*> currencies;

    for (const auto& currency: params.currencies)
    {
        if (currency.id == params.domesticCurrencyId) continue;

        if (currentIndex >= choleskyMatrix->n)
            throw std::runtime_error(
                "GlobalModelBuilder::createCurrencies: Size missmatch when initializing currencies"
                );

        PnlVect* volatilityVector = pnl_vect_create(choleskyMatrix->n);
        pnl_mat_get_row(volatilityVector, choleskyMatrix, currentIndex++);
        pnl_vect_mult_scalar(volatilityVector, currency.volatility);

        currencies.push_back(new Currency(
            currency.drift,
            volatilityVector,
            currency.interestRate,
            params.getDomesticRate()
            ));
    }

    return currencies;
}
