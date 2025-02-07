//
// Created by El Marjou on 03/02/2025.
//


#include <iostream>
#include <cassert>
#include <cmath>
#include <pnl/pnl_vector.h>
#include "financial/RiskyAsset.hpp"

void testRiskyAsset() {
    // Test setup
    PnlVect* volatilityVector = pnl_vect_create_from_scalar(1, 0.15); // Example volatility vector
    RiskyAsset asset(0.02, volatilityVector, 0.04); // Drift: 0.02, Domestic rate: 0.04

    // Test domestic interest rate
    assert(std::abs(asset.getDomesticRate() - 0.04) < 1e-6);
    std::cout << "Domestic interest rate test passed." << std::endl;

    // Test discount factor
    double discountFactor = asset.discount(0, 1); // exp(-0.04 * (1 - 0)) = exp(-0.04)
    assert(std::abs(discountFactor - std::exp(-0.04)) < 1e-6);
    std::cout << "Discount factor test passed." << std::endl;

    // Test capitalization factor
    double capitalizationFactor = asset.account(0, 1); // exp(0.04 * (1 - 0)) = exp(0.04)
    assert(std::abs(capitalizationFactor - std::exp(0.04)) < 1e-6);
    std::cout << "Capitalization factor test passed." << std::endl;

    // Clean up
    pnl_vect_free(&volatilityVector);
    std::cout << "All tests for RiskyAsset passed successfully." << std::endl;
}

int main() {
    testRiskyAsset();
    return 0;
}