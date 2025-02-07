//
// Created by ASUS on 06/02/2025.
//

#ifndef OPTIONBUILDER_HPP
#define OPTIONBUILDER_HPP
#include <nlohmann/adl_serializer.hpp>

#include "../options/CallCurrency.hpp"
#include "../options/CallQuanto.hpp"
#include "../options/ForeignAsianOption.hpp"
#include "../options/ForeignPerfBasket.hpp"
#include "../options/QuantoExchange.hpp"


class OptionBuilder {
public:
    /**
     * @brief Creates an Option from JSON configuration
     * @param params JSON parameters
     * @return Pointer to created Option
     * throws std::runtime_error if parameters are invalid
     */
    static Option* createFromJson(const nlohmann::json& params);

};



#endif //OPTIONBUILDER_HPP
