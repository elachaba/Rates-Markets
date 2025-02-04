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

int TimeGrid::indexLowerOrEqual(double t) const
{
    if (dates_.empty()) {
        throw std::runtime_error("TimeGrid is empty: no dates available.");
    }

    // Convert t to an integer threshold. If you want to handle fractional t differently,
    // you can use std::floor, std::ceil, or a direct cast.
    // This example uses floor, so if t=7.9, we look for the largest date <= 7.
    int target = static_cast<int>(std::floor(t));

    // We want the largest element in dates_ that is <= target.
    // upper_bound returns an iterator to the first element greater than 'target'.
    auto it = std::upper_bound(dates_.begin(), dates_.end(), target);

    if (it == dates_.begin()) {
        // Means all dates are > target -> none are <= t
        throw std::runtime_error("No date in the grid is <= the given time.");
    }

    // Otherwise, the largest date <= target is at 'it - 1'
    int index = static_cast<int>(it - dates_.begin()) - 1;
    return index;
}
