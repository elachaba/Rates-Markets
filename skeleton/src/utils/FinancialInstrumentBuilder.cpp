//
// Created by Aymane on 06/02/2025.
//

#include "FinancialInstrumentBuilder.hpp"

std::vector<int> FinancialInstrumentBuilder::buildAssetCorrelationMapping(const MarketParameters& params)
{
    std::map<std::string, int> currencyToIndex;
    currencyToIndex[params.domesticCurrencyId] = 0;

    int currencyIndex = 1;
    for (const auto& currency : params.currencies)
    {
        if (currency.id != params.domesticCurrencyId)
            currencyToIndex[currency.id] = currencyIndex++;
    }

    std::vector<int> mapping;
    mapping.reserve(params.assets.size());

    for (const auto& asset: params.assets)
    {
        int idx = currencyToIndex.at(asset.currencyId);
        mapping.push_back(idx);
    }

    return mapping;
}

std::pair<std::vector<InterestRateModel*>, InterestRateModel*>
    FinancialInstrumentBuilder::buildInterestRateModels(const MarketParameters& params)
{
    std::vector<InterestRateModel*> foreignRates;
    InterestRateModel* domesticRate = nullptr;

    for (const auto& currency : params.currencies)
    {
        if (currency.id == params.domesticCurrencyId)
            domesticRate = new InterestRateModel(currency.interestRate);
        else
            foreignRates.push_back(new InterestRateModel(currency.interestRate));
    }

    if (!domesticRate)
        throw std::runtime_error(
            "FinancialInstrumentBuilder::buildInterestRateModels: Domestic interest rate not found"
            );

    return {foreignRates, domesticRate};
}

PnlMat* FinancialInstrumentBuilder::createCholeskyMatrix(const PnlMat* correlationMatrix)
{
    if (!correlationMatrix)
        throw std::runtime_error(
            "FinancialInstrumentBuilder::createCholeskyMatrix: Correlation matrix is null"
            );

    PnlMat* cholesky = pnl_mat_copy(correlationMatrix);

    if (pnl_mat_chol(cholesky) != 0)
    {
        pnl_mat_free(&cholesky);
        throw std::runtime_error(
            "FinancialInstrumentBuilder::createCholeskyMatrix: Cholesky decomposition failed"
            );
    }

    return cholesky;
}


