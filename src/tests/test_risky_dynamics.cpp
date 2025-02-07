//
// Created by Aymane on 03/02/2025.
//

#include <iostream>
#include <cassert>
#include <cmath>
#include "models/RiskyDynamics.hpp"

void test_risky_dynamics() {
    std::cout << "=== Testing RiskyDynamics ===" << std::endl;

    // Create test volatility vector
    PnlVect* vol = pnl_vect_create_from_scalar(1, 0.2);  // 20% volatility

    // Test initialization
    double drift = 0.1;  // 10% drift
    RiskyDynamics dynamics(drift, vol);
    assert(std::abs(dynamics.getDrift() - drift) < 1e-10);
    std::cout << "Initialization test passed" << std::endl;


    // Test next value simulation
    double current_value = 100.0;
    double dt = 1.0/252.0;       // one day
    double dW = 0.0;             // zero Brownian increment for deterministic test

    double expected_value = current_value *
        std::exp((dynamics.getDrift() - 0.5 * 0.2 * 0.2) * dt);
    double computed_value = dynamics.sampleNextValue(current_value, dt, dW);

    assert(std::abs(computed_value - expected_value) < 1e-10);
    std::cout << "Next value simulation test passed" << std::endl;

    // Clean up
    pnl_vect_free(&vol);
}

int main() {
    test_risky_dynamics();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}