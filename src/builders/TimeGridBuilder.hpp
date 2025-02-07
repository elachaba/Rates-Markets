//
// Created by A on 0ymane6/02/2025.
//

#ifndef TIMEGRIDBUILDER_HPP
#define TIMEGRIDBUILDER_HPP
#include <nlohmann/adl_serializer.hpp>

#include "../utils/ITimeGrid.hpp"


class TimeGridBuilder {
public:
    /**
     * Creates time grid from JSON configuration
     * @param params JSON object containing parameters
     * @return Pointer to created ITimeGrid instance
     * @throws std::runtimne_error if parameters are invalid
     */
    static ITimeGrid* createFromJson(const nlohmann::json& params);

    /**
     * Creates time grid from JSON configuration
     * @param params JSON object containing parameters
     * @return Pointer to created ITimeGrid instance
     * @throws std::runtimne_error if parameters are invalid
     */
    static ITimeGrid* createRebalancingFromJson(const nlohmann::json& params);
};

#endif //TIMEGRIDBUILDER_HPP
