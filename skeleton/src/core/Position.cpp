//
// Created by Aymane on 03/02/2025.
//

#include "Position.hpp"
#include "utils/json_reader.hpp"
#include <pnl/pnl_vector.h>

Position::Position(int date,
                   double price,
                   double priceStdDev,
                   PnlVect* deltas,
                   PnlVect* deltasStdDev,
                   double portfolioValue)
        : date_(date)
        , price_(price)
        , priceStdDev_(priceStdDev)
        , portfolioValue_(portfolioValue)
{
    if (deltas == nullptr || deltasStdDev == nullptr)
        throw std::runtime_error("Deltas vectors cannot be null");

    deltas_ = pnl_vect_copy(deltas);
    deltasStdDev_ = pnl_vect_copy(deltasStdDev);
}

Position::~Position()
{
    pnl_vect_free(&deltas_);
    pnl_vect_free(&deltasStdDev_);
}

void Position::print() const
{
    nlohmann::json j = *this;
    std::cout << j.dump(4) << std::endl;
}

void to_json(nlohmann::json &j, const Position &position) {
        j["date"] = position.date_;
        j["value"] = position.portfolioValue_;
        j["price"] = position.price_;
        j["priceStdDev"] = position.priceStdDev_;
        j["deltas"] = position.deltas_;
        j["deltasStdDev"] = position.deltasStdDev_;
}

double Position::computeValue(const PnlVect* spots) const {
    if (spots->size != deltas_->size) {
        throw std::runtime_error("Incompatible sizes between spots and deltas");
    }

    double value = pnl_vect_scalar_prod(deltas_, spots);
    return value;
}

