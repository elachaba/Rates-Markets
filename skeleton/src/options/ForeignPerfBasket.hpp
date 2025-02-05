//
// Created by Aymane on 05/02/2025.
//

#ifndef FOREIGNPERFBASKET_HPP
#define FOREIGNPERFBASKET_HPP
#include <utility>

#include "Option.hpp"


class ForeignPerfBasket : public Option {
private:
    std::vector<int> nbAssetsPerCurrency_;
    double strikePrice_;

public:
    ForeignPerfBasket(const std::vector<int>& assetCurrencyMapping,
           const std::vector<InterestRateModel*>& foreignInterestRates,
           InterestRateModel* domesticInterestRate,
           ITimeGrid* monitoringTimeGrid,
           double strikePrice,
           std::vector<int> nbAssetsPerCurrency
           )
        : Option(assetCurrencyMapping, foreignInterestRates_, domesticInterestRate, monitoringTimeGrid)
        , nbAssetsPerCurrency_(std::move(nbAssetsPerCurrency))
        , strikePrice_(strikePrice) {}

    /**
     * @brief Computes payoff of a foreign performance basket option
     * @param path Prices of underlying assets
     */
    double payoff(const PnlMat* path) const override;


};


#endif //FOREIGNPERFBASKET_HPP
