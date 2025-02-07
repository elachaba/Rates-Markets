//

// Created by Aymane on 04/02/2025.

//


// test_global_model.cpp

#include <iostream>
#include <fstream>
#include "models/GlobalModel.hpp"
#include "builders/GlobalModelBuilder.hpp"
#include "nlohmann/json.hpp"

void testGlobalModel() {
    try {
        // Read JSON file
        std::ifstream file("C:/Users/ASUS/source/repos/Rates-Markets/data-benchmark/foreign_perf_basket_params.json");
        if (!file.is_open()) {
            std::cerr << "Error: Cannot open JSON file" << std::endl;
            return;
        }
        nlohmann::json jsonParams = nlohmann::json::parse(file);

        // Create model
        GlobalModel* model = GlobalModelBuilder::createFromJson(jsonParams);

        // Test basic initialization
        std::cout << "Testing basic initialization..." << std::endl;
        std::cout << "Number of risky assets: " << model->getRiskyAssets().size()
                  << " (expected: 6)" << std::endl;
        std::cout << "Number of foreign currencies: " << model->getCurrencies().size()
                  << " (expected: 2)" << std::endl;

        // Test currencies initialization
        std::cout << "\nTesting currencies..." << std::endl;
        for (const auto* currency : model->getCurrencies()) {
            std::cout << "Currency with rate " << currency->getForeignRate()
                     << " and volatility ";
            pnl_vect_print_asrow(currency->getVolatility());
            std::cout << " and drift " << currency->getDrift() << std::endl;
        }

        // Test assets initialization
        std::cout << "\nTesting assets..." << std::endl;
        int usdAssets = 0, gbpAssets = 0, eurAssets = 0;
        for (const auto* asset : model->getRiskyAssets()) {
            std::string currencyId = asset->getCurrencyId();
            if (currencyId == "us_dollar") usdAssets++;
            else if (currencyId == "pound") gbpAssets++;
            else if (currencyId == "eur") eurAssets++;

            std::cout << "Asset in " << currencyId
                     << " with volatility ";
            pnl_vect_print_asrow(asset->getVolatility());
            std::cout << " and drift " << asset->getDrift() << std::endl;
        }

        std::cout << "\nAssets per currency:"
                  << "\nEUR assets: " << eurAssets << " (expected: 1)"
                  << "\nUSD assets: " << usdAssets << " (expected: 2)"
                  << "\nGBP assets: " << gbpAssets << " (expected: 3)" << std::endl;

        // Test time grid
        std::cout << "\nTesting time grid..." << std::endl;
        double expectedNumberOfDates = 3;
        std::cout << "Number of dates in time grid maturity: " << model->getTimeGrid()->len()
                  << " (expected: " << expectedNumberOfDates << ")" << std::endl;

        delete model;
        std::cout << "\nAll tests completed successfully!" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error during testing: " << e.what() << std::endl;
    }
}

int main() {
    std::cout << "Starting GlobalModel tests..." << std::endl;
    testGlobalModel();
    return 0;
}