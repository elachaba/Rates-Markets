//
// Created by Aymane on 03/02/2025.
//

#ifndef POSITION_HPP
#define POSITION_HPP
#include <iostream>
#include <stdexcept>
#include <nlohmann/json.hpp>
#include <pnl/pnl_vector.h>

class Position {
public:
    int date_;
    double price_;
    double priceStdDev_;
    double portfolioValue_;
    PnlVect *deltas_;
    PnlVect *deltasStdDev_;

    Position(int date,
        double price,
        double priceStdDev,
        PnlVect *deltas,
        PnlVect *deltasStdDev,
        double portfolioValue
        );

    virtual ~Position();

    /**
     * @brief Print position details
     */
    void print() const;

    /**
     * @brief Convert position to JSON
     */
    friend void to_json(nlohmann::json &j, const Position &p);

    /**
     * @brief Compute position value
     * @param spots Current market spots
     */
    double computeValue(const PnlVect* spots) const;

};
#endif //POSITION_HPP
