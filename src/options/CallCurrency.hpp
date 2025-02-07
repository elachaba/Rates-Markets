//
// Created by Aymane on 05/02/2025.
//

#ifndef CALLCURRENCY_HPP
#define CALLCURRENCY_HPP
#include "Option.hpp"


/**
 * @brief Call option on a foreign currency (Call Currency)
 */
class CallCurrency : public Option{

private:
    double strikePrice_;

public:
    CallCurrency(const std::vector<int>& assetCurrencyMapping,
            const std::vector<InterestRateModel*>& foreignRates,
            InterestRateModel* domesticRate,
            ITimeGrid* monitoringGrid,
            double strikePrice)
        : Option(assetCurrencyMapping, foreignRates, domesticRate, monitoringGrid)
        , strikePrice_(strikePrice) {}

    /**
     * @brief Computes the payoff of a currency call option
     * @param path Path of the price of the underlying assets
     * @return X^1_T * e^{r^1 T} - K
     */
    double payoff(const PnlMat* path) const override;
};




#endif //CALLCURRENCY_HPP
