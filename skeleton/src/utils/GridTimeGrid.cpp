//
// Created by Aymane on 03/02/2025.
//

#include "GridTimeGrid.hpp"
#include <algorithm>
#include <stdexcept>
#include <nlohmann/json.hpp>
#include <utility>



GridTimeGrid::GridTimeGrid(std::vector<int> dates) : dates_(std::move(dates)) {}

int GridTimeGrid::at(int index) const {
    if (index < 0 || index >= static_cast<int>(dates_.size())) {
        throw std::out_of_range("Index is out of range.");
    }
    return dates_[index];
}

int GridTimeGrid::len() const {
    return static_cast<int>(dates_.size());
}

bool GridTimeGrid::has(int nDays) const {
    return std::binary_search(dates_.begin(), dates_.end(), nDays);
}
