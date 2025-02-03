//
// Created by Aymane on 03/02/2025.
//

#include <iostream>
#include <cassert>
#include "core/Position.hpp"

void test_position() {
    std::cout << "=== Testing Position ===" << std::endl;

    // Create test vectors
    PnlVect* deltas = pnl_vect_create_from_scalar(3, 0.5);      // 3 assets, delta = 0.5
    PnlVect* deltasStd = pnl_vect_create_from_scalar(3, 0.01);  // std dev = 0.01

    // Test initialization
    Position pos(1, 100.0, 0.5, deltas, deltasStd, 105.0);
    assert(pos.date_ == 1);
    assert(std::abs(pos.price_ - 100.0) < 1e-10);
    assert(std::abs(pos.priceStdDev_ - 0.5) < 1e-10);
    assert(std::abs(pos.portfolioValue_ - 105.0) < 1e-10);
    std::cout << "Initialization test passed" << std::endl;

    // Test value computation
    PnlVect* spots = pnl_vect_create_from_scalar(3, 100.0);
    double expected_value = 3 * 0.5 * 100.0;  // 3 assets * delta * spot
    double computed_value = pos.computeValue(spots);
    assert(std::abs(computed_value - expected_value) < 1e-10);
    std::cout << "Value computation test passed" << std::endl;

    // Test JSON serialization
    nlohmann::json j;
    to_json(j, pos);
    assert(j["date"] == 1);
    assert(std::abs(j["price"].get<double>() - 100.0) < 1e-10);
    std::cout << "JSON serialization test passed" << std::endl;

    // Clean up
    pnl_vect_free(&deltas);
    pnl_vect_free(&deltasStd);
    pnl_vect_free(&spots);
}

int main() {
    test_position();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
