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
    double portfolioValue_;  // Added portfolio value
    PnlVect *deltas_;
    PnlVect *deltasStdDev_;

private:
    double cashValue_;


public:
    Position(int date,
        double price,
        double priceStdDev,
        PnlVect *deltas,
        PnlVect *deltasStdDev,
        double cashValue,
        double portfolioValue);

    Position(const Position& other);

    Position& operator=(const Position& other)
    {
        if (this != &other) {
            date_ = other.date_;
            price_ = other.price_;
            priceStdDev_ = other.priceStdDev_;
            cashValue_ = other.cashValue_;
            portfolioValue_ = other.portfolioValue_;

            // Free existing vectors
            if (deltas_) pnl_vect_free(&deltas_);
            if (deltasStdDev_) pnl_vect_free(&deltasStdDev_);

            // Copy new vectors
            deltas_ = pnl_vect_copy(other.deltas_);
            deltasStdDev_ = pnl_vect_copy(other.deltasStdDev_);
        }
        return *this;
    }


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
     * @param dt Time between the two rebalancing dates in years
     * @param riskFreeRate Domestic risk free rate
     */
    double computeValue(const PnlVect* spots, double dt, double riskFreeRate) const;

};
#endif //POSITION_HPP
