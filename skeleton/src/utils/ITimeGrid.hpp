//
// Created by Aymane on 05/02/2025.
//

#ifndef ITIMEGRID_HPP
#define ITIMEGRID_HPP

/**
 * @brief Interface for a time grid.
 */
class ITimeGrid {
public:

    /**
     * @brief Returns the date at a given index.
     * @param index The index of the date.
     * @return The corresponding date (integer).
     * @throw std::out_of_range If the index is invalid.
     */
    virtual int at(int index) const = 0;

    /**
     * @brief Returns the total number of dates in the grid.
     * @return The number of dates.
     */
    virtual int len() const = 0;

    /**
     * @brief Checks if a specific date exists in the grid.
     * @param nDays The date to check.
     * @return true if the date exists, false otherwise.
     */
    virtual bool has(int nDays) const = 0;

    /**
     * 
     * @return Number of days in one year
     */
    virtual int getNumberOfDaysInYear() const = 0;

    virtual ~ITimeGrid() = default;
};

#endif //ITIMEGRID_HPP
