//
// Created by ASUS on 05/02/2025.
//

#include "FixedTimeGrid.hpp"
#include <stdexcept>

FixedTimeGrid::FixedTimeGrid(int maturityInDays, int period)
    : maturityInDays_(maturityInDays)
    , period_(period)
{
    if (maturityInDays_ < 0)
        throw std::invalid_argument("maturityInDays must be >= 0");

    if (period_ < 0)
        throw std::invalid_argument("period must be >= 0");
}

int FixedTimeGrid::at(int index) const
{
    if (index < 0)
        throw std::out_of_range("FixedTimeGrid::at : index must be >= 0");

    int date = index * period_;

    if (date > maturityInDays_)
        throw std::out_of_range("FixedTimeGrid::at : index out of grid bound");

    return date;
}

int FixedTimeGrid::len() const
{
    return (maturityInDays_ / period_) + 1;
}

bool FixedTimeGrid::has(int nDays) const
{
    if (nDays < 0 || nDays > maturityInDays_)
        return false;

    return nDays % period_ == 0;
}

