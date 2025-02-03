//
// Created by Aymane on 03/02/2025.
//

#ifndef TIMEGRID_HPP
#define TIMEGRID_HPP

#include <vector>
#include <nlohmann/json.hpp>

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

    virtual ~ITimeGrid() = default;
};

/**
 * @brief Class implementing a time grid from a JSON description.
 */
class TimeGrid : public ITimeGrid {
private:
    std::vector<int> dates_; ///< List of dates in the grid.

public:
    /**
     * @brief Constructor using a JSON description.
     * @param timeGridDesc A JSON object containing a list of dates.
     * @throw std::invalid_argument If the JSON is invalid or does not contain a valid list.
     */
    explicit TimeGrid(const nlohmann::json& timeGridDesc);

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
};

#endif // TIMEGRID_HPP
