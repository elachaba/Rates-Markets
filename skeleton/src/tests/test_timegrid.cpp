//
// Created by El Marjou on 03/02/2025.
//


#include <iostream>
#include <cassert>
#include <nlohmann/json.hpp>
#include "utils/TimeGrid.hpp"

void test_timegrid() {
    // Test 1: Construct TimeGrid with valid JSON
    nlohmann::json jsonData = {1, 5, 10, 20};
    TimeGrid grid(jsonData);

    // Test length function
    assert(grid.len() == 4);
    std::cout << "Test len() passed." << std::endl;

    // Test at() function
    assert(grid.at(0) == 1);
    assert(grid.at(1) == 5);
    assert(grid.at(2) == 10);
    assert(grid.at(3) == 20);
    std::cout << "Test at() passed." << std::endl;

    // Test has() function
    assert(grid.has(5) == true);
    assert(grid.has(10) == true);
    assert(grid.has(15) == false);
    std::cout << "Test has() passed." << std::endl;

    // Test exception handling for at() function
    try {
        grid.at(4); // Out of bounds
        std::cerr << "Test failed: at(4) should throw an exception." << std::endl;
        assert(false);
    } catch (const std::out_of_range&) {
        std::cout << "Test out_of_range exception passed." << std::endl;
    }

    // Test constructor with invalid JSON (not an array)
    try {
        nlohmann::json invalidJson = {{"invalid", 123}};
        TimeGrid badGrid(invalidJson);
        std::cerr << "Test failed: Invalid JSON should throw an exception." << std::endl;
        assert(false);
    } catch (const std::invalid_argument&) {
        std::cout << "Test invalid JSON exception passed." << std::endl;
    }

    std::cout << "All tests passed successfully!" << std::endl;
}

int main() {
    test_timegrid();
    return 0;
}
