//
// Created by El Marjou on 03/02/2025.
//


#include "utils/TimeGrid.hpp"
#include <iostream>

int main() {
    nlohmann::json timeGridDesc = {1, 10, 5, 20}; // Example JSON array
    try {
        TimeGrid timeGrid(timeGridDesc);

        std::cout << "Length: " << timeGrid.len() << std::endl;
        std::cout << "Date at index 2: " << timeGrid.at(2) << std::endl;
        std::cout << "Has date 10? " << (timeGrid.has(10) ? "Yes" : "No") << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}