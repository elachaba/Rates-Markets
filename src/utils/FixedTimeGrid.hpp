//
// Created by Aymane on 05/02/2025.
//

#ifndef FIXEDTIMEGRID_HPP
#define FIXEDTIMEGRID_HPP

#include "../utils/ITimeGrid.hpp"


/**
 * @brief Class implementing a time grid with a fixed time step.
 */
class FixedTimeGrid : public ITimeGrid {
private:
    int maturityInDays_;
    int period_;
    int numberOfDaysInYear_;

public:
    /**
     * @brief Constructor using a JSON description.
     * @param maturityInDays The last date of the grid.
     * @param period Time step between two date.
     */
    explicit FixedTimeGrid(int maturityInDays, int period, int numberOfDaysInYear);

    /**
     * @brief Returns the date at a given index.
     * @param index The index of the date.
     * @return The corresponding date.
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

    int getNumberOfDaysInYear() const override { return numberOfDaysInYear_; }

    int getMaturity() const override { return maturityInDays_; }
};


#endif //FIXEDTIMEGRID_HPP
