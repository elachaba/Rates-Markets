//
// Created by Aymane on 05/02/2025.
//

#ifndef CALLQUANTO_HPP
#define CALLQUANTO_HPP
#include "Option.hpp"


/**
 * @brief Call option on a foreign stock (Call Quanto)
 */
class CallQuanto : public Option {
private:
    double strikePrice_;

public:
    CallQuanto(const std::vector<int>& assetCurrencyMapping,
            const std::vector<InterestRateModel*>& foreignRates,
            InterestRateModel* domesticRate,
            ITimeGrid* monitoringGrid,
            double strike)
    : Option(assetCurrencyMapping, foreignRates, domesticRate, monitoringGrid)
    , strikePrice_(strike) {}


    /**
     * @brief Computes the payoff of a call quanto option
     * @param path Path of the price of underlying assets
     * @return S^{1,1}_T X^1_T - K
     */
    double payoff(const PnlMat* path) const override;
};



#endif //CALLQUANTO_HPP
