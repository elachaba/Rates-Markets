//
// Created by Aymane on 03/02/2025.
//

#ifndef GRID_TIMEGRID_HPP
#define GRID_TIMEGRID_HPP

#include <vector>
#include <utils/ITimeGrid.hpp>


/**
 * @brief Class implementing a time grid with a vector of dates.
 */
class GridTimeGrid : public ITimeGrid {
private:
    std::vector<int> dates_; ///< List of dates in the grid.
    int numberOfDaysInYear_;

public:
    /**
     * @brief Constructor using a JSON description.
     * @param dates List of dates in the time grid
     */
    explicit GridTimeGrid(std::vector<int> dates, int numberOfDaysInYear);

    /**
     * @brief Returns the date at a given index.
     * @param index The index of the date.
     * @return The corresponding date.
     * @throw std::out_of_range If the index is invalid.
     */
    int at(int index) const override;

    /**
     * @brief Returns the total number of dates in the grid.
     * @return The number of dates.
     */
    int len() const override;

    /**
     * @brief Checks if a specific date exists in the grid.
     * @param nDays The date to check.
     * @return true if the date exists, false otherwise.
     */
    bool has(int nDays) const override;

    int getNumberOfDaysInYear() const override { return numberOfDaysInYear_; };

};

#endif // GRID_TIMEGRID_HPP
