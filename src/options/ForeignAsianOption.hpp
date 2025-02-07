//
// Created by Aymane on 05/02/2025.
//

#ifndef FOREIGNASIANOPTION_HPP
#define FOREIGNASIANOPTION_HPP
#include <vector>
#include <pnl/pnl_matvect.h>

#include "Option.hpp"
#include "../financial/InterestRateModel.hpp"
#include "../utils/ITimeGrid.hpp"


/**
 * @brief Asian Option on a foreign currency
 */
class ForeignAsianOption : public Option {
public:
    ForeignAsianOption(const std::vector<int>& assetCurrencyMapping,
           const std::vector<InterestRateModel*>& foreignInterestRates,
           InterestRateModel* domesticInterestRate,
           ITimeGrid* monitoringTimeGrid
           )
               : Option(assetCurrencyMapping, foreignInterestRates, domesticInterestRate, monitoringTimeGrid) {}

    /**
     * @brief Computes the payoff of a foreign asian option
     * @param path Prices of the underlying assets
     * @return (1/N ∑(X^1_tj * S^1_tj) - S^0_T)_+
     */
    double payoff(const PnlMat* path) const override;

};



#endif //FOREIGNASIANOPTION_HPP
