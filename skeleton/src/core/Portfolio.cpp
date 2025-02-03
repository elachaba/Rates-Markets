#include <iostream>
#include "Portfolio.hpp"
#include "utils/json_reader.hpp"



Portfolio::Portfolio(nlohmann::json &jsonParams, MonteCarlo &monteCarlo)
    : monteCarlo(monteCarlo) {

}

Portfolio::~Portfolio() {
}

