//
// Created by ASUS on 06/02/2025.
//

#include "TimeGridBuilder.hpp"

#include <nlohmann/json.hpp>

#include "../utils/FixedTimeGrid.hpp"
#include "../utils/GridTimeGrid.hpp"

ITimeGrid* TimeGridBuilder::createFromJson(const nlohmann::json& params)
{
    int numberDaysInYear = params.at("NumberOfDaysInOneYear");
    nlohmann::json timeGridParams = params.at("Option").at("FixingDatesInDays");
    std::string gridType = timeGridParams.at("Type");

    if (gridType == "Fixed")
    {
        int maturity = params.at("Option").at("MaturityInDays").get<int>();
        int period = timeGridParams.at("Period").get<int>();

        return new FixedTimeGrid(maturity, period, numberDaysInYear);
    }

    if (gridType == "Grid")
    {
        std::vector<int> dates = timeGridParams.at("DatesInDays").get<std::vector<int>>();

        return new GridTimeGrid(dates, numberDaysInYear);
    }

    throw std::runtime_error("TimeGridBuilder::createFromJson: Unknown grid type");
}

ITimeGrid* TimeGridBuilder::createRebalancingFromJson(const nlohmann::json& params)
{
    int numberDaysInYear = params.at("NumberOfDaysInOneYear");
    nlohmann::json timeGridParams = params.at("Option").at("FixingDatesInDays");
    std::string gridType = params.at("PortfolioRebalancingOracleDescription").at("Type");

    if (gridType == "Fixed")
    {
        int maturity = params.at("Option").at("MaturityInDays").get<int>();
        int period = params.at("PortfolioRebalancingOracleDescription").at("Period").get<int>();

        return new FixedTimeGrid(maturity, period, numberDaysInYear);
    }

    if (gridType == "Grid")
    {
        std::vector<int> dates = timeGridParams.at("DatesInDays").get<std::vector<int>>();

        return new GridTimeGrid(dates, numberDaysInYear);
    }

    throw std::runtime_error("TimeGridBuilder::createFromJson: Unknown grid type");
}