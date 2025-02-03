#pragma once

#include <list>
#include "MonteCarlo.hpp"
#include "utils/TimeGrid.hpp"
#include "Position.hpp"

class Portfolio {
public:
    MonteCarlo &monteCarlo;
    std::list<Position> positions;

    Portfolio(nlohmann::json &jsonParams, MonteCarlo &monteCarlo);
    ~Portfolio();
};
