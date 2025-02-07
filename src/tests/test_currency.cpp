//
// Created by El Marjou on 03/02/2025.
//

#include <iostream>
#include <cassert>
#include <cmath>
#include <pnl/pnl_vector.h>
#include "models/Currency.hpp"

void testCurrency() {
    // Test setup
    PnlVect* volatilityVector = pnl_vect_create_from_scalar(1, 0.2); // Example volatility vector
    Currency currency(0.01, volatilityVector, 0.05, 0.03); // Drift: 0.01, Foreign rate: 0.05, Domestic rate: 0.03

    // Test foreign interest rate
    assert(currency.getForeignRate() == 0.05);
    std::cout << "Foreign interest rate test passed." << std::endl;

    // Test domestic interest rate
    assert(currency.getDomesticRate() == 0.03);
    std::cout << "Domestic interest rate test passed." << std::endl;

    // Test discount factors
    double foreignDiscount = currency.discountForeign(0, 1); // exp(-0.05 * (1 - 0)) = exp(-0.05)
    double domesticDiscount = currency.discountDomestic(0, 1); // exp(-0.03 * (1 - 0)) = exp(-0.03)

    assert(std::abs(foreignDiscount - std::exp(-0.05)) < 1e-6);
    assert(std::abs(domesticDiscount - std::exp(-0.03)) < 1e-6);
    std::cout << "Discount factor tests passed." << std::endl;

    // Test capitalization factors
    double foreignAccount = currency.accountForeign(0, 1); // exp(0.05 * (1 - 0)) = exp(0.05)
    double domesticAccount = currency.accountDomestic(0, 1); // exp(0.03 * (1 - 0)) = exp(0.03)

    assert(std::abs(foreignAccount - std::exp(0.05)) < 1e-6);
    assert(std::abs(domesticAccount - std::exp(0.03)) < 1e-6);
    std::cout << "Capitalization factor tests passed." << std::endl;

    // Clean up
    pnl_vect_free(&volatilityVector);
    std::cout << "All tests for Currency passed successfully." << std::endl;
}

int main() {
    testCurrency();
    return 0;
}
