//
// Created by Aymane on 03/02/2025.
//

#include "Position.hpp"
#include "../utils/json_reader.hpp"
#include <pnl/pnl_vector.h>

Position::Position(int date,
        double price,
        double priceStdDev,
        PnlVect *deltas,
        PnlVect *deltasStdDev,
        double cashValue,
        double portfolioValue)  // Added portfolio value parameter
        : date_(date)
        , price_(price)
        , priceStdDev_(priceStdDev)
        , cashValue_(cashValue)
        , portfolioValue_(portfolioValue)
{
    if (deltas == nullptr || deltasStdDev == nullptr)
        throw std::runtime_error("Deltas vectors cannot be null");

    deltas_ = pnl_vect_copy(deltas);
    deltasStdDev_ = pnl_vect_copy(deltasStdDev);
}

Position::Position(const Position& other)
    : date_(other.date_)
    , price_(other.price_)
    , priceStdDev_(other.priceStdDev_)
    , cashValue_(other.cashValue_)
    , portfolioValue_(other.portfolioValue_)
{
    deltas_ = pnl_vect_copy(other.deltas_);
    deltasStdDev_ = pnl_vect_copy(other.deltasStdDev_);
}

Position::~Position()
{
    std::cout << "Position destructor called" << std::endl;
    if (deltas_ != nullptr)
        pnl_vect_free(&deltas_);

    if (deltasStdDev_ != nullptr)
        pnl_vect_free(&deltasStdDev_);
}

void Position::print() const
{
    nlohmann::json j = *this;
    std::cout << j.dump(4) << std::endl;
}

void to_json(nlohmann::json &j, const Position &position) {
        j["date"] = position.date_;
        j["deltas"] = position.deltas_;
        j["deltasStdDev"] = position.deltasStdDev_;
        j["price"] = position.price_;
        j["priceStdDev"] = position.priceStdDev_;
        j["value"] = position.portfolioValue_;

}

double Position::computeValue(const PnlVect* spots, double dt, double riskFreeRate) const {
    if (spots->size != deltas_->size) {
        throw std::runtime_error("Position::computeValue: Incompatible sizes between spots and deltas");
    }

    double riskyValue = pnl_vect_scalar_prod(deltas_, spots);
    double updatedCashValue = cashValue_ * std::exp(riskFreeRate * dt);
    return riskyValue + updatedCashValue;
}

