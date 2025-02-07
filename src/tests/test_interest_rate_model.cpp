//
// Created by A on 0ymane3/02/2025.
//

#include <iostream>
#include <cmath>
#include <cassert>
#include "financial/InterestRateModel.hpp"

void test_interest_rate_model() {
    std::cout << "=== Testing InterestRateModel ===" << std::endl;

    // Test initialization
    double rate = 0.05;  // 5% interest rate
    InterestRateModel model(rate);
    assert(std::abs(model.getRate() - rate) < 1e-10);
    std::cout << "Initialization test passed" << std::endl;

    // Test discount factor
    double t1 = 0.0;
    double t2 = 1.0;
    double expected_discount = std::exp(-rate * (t2 - t1));
    double computed_discount = model.discount(t1, t2);
    assert(std::abs(computed_discount - expected_discount) < 1e-10);
    std::cout << "Discount factor test passed" << std::endl;

    // Test account factor
    double expected_account = std::exp(rate * (t2 - t1));
    double computed_account = model.account(t1, t2);
    assert(std::abs(computed_account - expected_account) < 1e-10);
    std::cout << "Account factor test passed" << std::endl;

    // Test consistency between discount and account
    assert(std::abs(computed_discount * computed_account - 1.0) < 1e-10);
    std::cout << "Consistency test passed" << std::endl;
}

// Main function
int main() {
    test_interest_rate_model();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
