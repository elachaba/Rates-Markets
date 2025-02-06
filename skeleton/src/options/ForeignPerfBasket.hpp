//
// Created by Aymane on 05/02/2025.
//

#ifndef FOREIGNPERFBASKET_HPP
#define FOREIGNPERFBASKET_HPP
#include <utility>

#include "Option.hpp"


class ForeignPerfBasket : public Option {
private:
    double strikePrice_;

public:
    ForeignPerfBasket(const std::vector<int>& assetCurrencyMapping,
           const std::vector<InterestRateModel*>& foreignInterestRates,
           InterestRateModel* domesticInterestRate,
           ITimeGrid* monitoringTimeGrid,
           double strikePrice
           )
        : Option(assetCurrencyMapping, foreignInterestRates_, domesticInterestRate, monitoringTimeGrid)
        , strikePrice_(strikePrice) {}

    /**
     * @brief Computes payoff of a foreign performance basket option
     * @param path Prices of underlying assets
     */
    double payoff(const PnlMat* path) const override;

private:
    /**
     * @brief Computes the average of the prices of all assets of a currency at a date
     * @param path Matrix of prices of all underlying assets in monitoring dates
     * @param date Time to calculate the average
     * @param currencyId Number that represents the currency
     * @return Average of the prices of all assets of a currency at a date
     */
    double computeBasketAverage(const PnlMat* path, int date, size_t currencyId) const;

    /**
    *
    * @param path Matrix of prices of all underlying assets in monitoring dates
    * @param currencyId Number that represents the currency
    * @param numAssets Number of assets in the currency
    * @return
    */
    double computeCurrencyPerformance(const PnlMat* path, int currencyId, int numAssets) const;

    /**
     *
     * @return Total number of underlying  risky assets not including exchange rates
     */
    size_t getTotalNumberOfAssets() const;

    /**
     *
     * @return a vector of the numbers identifying currencies
     */
    std::vector<int> getUniqueCurrencies() const;

};


#endif //FOREIGNPERFBASKET_HPP
