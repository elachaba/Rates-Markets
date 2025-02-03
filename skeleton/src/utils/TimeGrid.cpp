//
// Created by Aymane on 03/02/2025.
//

#include "TimeGrid.hpp"
#include <algorithm>
#include <stdexcept>
#include <nlohmann/json.hpp>


/**
 * @brief Constructor: Initializes the TimeGrid using a JSON description.
 * @param timeGridDesc JSON object containing a list of dates.
 * @throw std::invalid_argument If the JSON is invalid or does not contain a valid list.
 */
TimeGrid::TimeGrid(const nlohmann::json& timeGridDesc) {
    if (!timeGridDesc.is_array()) {
        throw std::invalid_argument("The provided JSON must be an array of integers.");
    }
    for (const auto& value : timeGridDesc) {
        if (!value.is_number_integer()) {
            throw std::invalid_argument("The JSON array must contain only integers.");
        }
        dates_.push_back(value.get<int>());
    }

    // Ensure the dates are sorted (optional, depending on use case)
    std::sort(dates_.begin(), dates_.end());
}

/**
 * @brief Returns the date at a given index.
 * @param index The index of the date.
 * @return The corresponding date.
 * @throw std::out_of_range If the index is invalid.
 */
int TimeGrid::at(int index) const {
    if (index < 0 || index >= static_cast<int>(dates_.size())) {
        throw std::out_of_range("Index is out of range.");
    }
    return dates_[index];
}

/**
 * @brief Returns the total number of dates in the grid.
 * @return The number of dates.
 */
int TimeGrid::len() const {
    return static_cast<int>(dates_.size());
}

/**
 * @brief Checks if a specific date exists in the grid.
 * @param nDays The date to check.
 * @return true if the date exists, false otherwise.
 */
bool TimeGrid::has(int nDays) const {
    return std::binary_search(dates_.begin(), dates_.end(), nDays);
}
