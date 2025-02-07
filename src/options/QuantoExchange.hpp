//
// Created by Aymane on 05/02/2025.
//

#ifndef QUANTOEXCHANGE_HPP
#define QUANTOEXCHANGE_HPP
#include "Option.hpp"

/**
 * @brief Exchange option on a foreign asset
 */
class QuantoExchange : public Option {
private:
    double strikePrice_;
public:
    QuantoExchange(const std::vector<int>& assetCurrencyMapping,
           const std::vector<InterestRateModel*>& foreignInterestRates,
           InterestRateModel* domesticInterestRate,
           ITimeGrid* monitoringTimeGrid,
           double strikePrice
           )
               : Option(assetCurrencyMapping, foreignInterestRates, domesticInterestRate, monitoringTimeGrid)
                , strikePrice_(strikePrice) {}

    /**
     * @brief Computes the payoff of a quanto exchange option
     * @param path Prices of the underlying assets
     * @return S^{0,1}_T - S^{1,1}_T X^1_T - K
     */
    double payoff(const PnlMat* path) const override;

};



#endif //QUANTOEXCHANGE_HPP
