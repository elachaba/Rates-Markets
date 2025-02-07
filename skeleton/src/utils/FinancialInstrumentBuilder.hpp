//
// Created by Aymane on 06/02/2025.
//

#ifndef FINANCIALINSTRUMENTBUILDER_HPP
#define FINANCIALINSTRUMENTBUILDER_HPP

#include <vector>

#include "MarketParameters.hpp"
#include "financial/InterestRateModel.hpp"


class FinancialInstrumentBuilder {
public:

    /**
     * @brief Build mapping between assets and their currencies
     * @param params Market parameters
     * @return Vector where index i contains the currency index for asset i
     */
    static std::vector<int> buildAssetCorrelationMapping(const MarketParameters& params);

    /**
     * @brief Build interest rate models for all currencies
     * @param params Market parameters
     * @return Pair of (foreign rates vector, domestic rate)
     */
    static std::pair<std::vector<InterestRateModel*>, InterestRateModel*>
        buildInterestRateModels(const MarketParameters& params);


    /**
     * @brief Create Cholesky decomposition of correlation matrix
     * @param correlationMatrix Original correlation matrix
     * @return Cholesky decomposed matrix
     * @throw std::runtime_error if decomposition fails
     */
    static PnlMat* createCholeskyMatrix(const PnlMat* correlationMatrix);

};



#endif //FINANCIALINSTRUMENTBUILDER_HPP
