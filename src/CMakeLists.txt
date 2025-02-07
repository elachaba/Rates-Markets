cmake_minimum_required(VERSION 3.20.0)
project(FXHedging CXX)

# Release or Debug
if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "Setting build type to 'Debug' as none was specified.")
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
endif ()

# Find required packages
find_package(Pnl REQUIRED)
find_package(nlohmann_json REQUIRED)

# Use gtest
find_package(GTest REQUIRED)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PNL_INCLUDE_DIRS})

# Add source files
set(SOURCE_FILES
        utils/json_reader.cpp
        utils/json_reader.hpp
        core/MonteCarlo.hpp
        core/MonteCarlo.cpp
        core/Position.hpp
        core/Position.cpp
        core/Portfolio.cpp
        core/Portfolio.hpp
        models/GlobalModel.cpp
        models/GlobalModel.hpp
        models/RiskyDynamics.cpp
        models/RiskyDynamics.hpp
        models/Currency.cpp
        models/Currency.hpp
        options/Option.hpp
        financial/RiskyAsset.cpp
        financial/RiskyAsset.hpp
        financial/InterestRateModel.cpp
        financial/InterestRateModel.hpp
        utils/GridTimeGrid.cpp
        utils/GridTimeGrid.hpp
        builders/GlobalModelBuilder.cpp
        builders/GlobalModelBuilder.hpp
        utils/ITimeGrid.hpp
        utils/FixedTimeGrid.cpp
        utils/FixedTimeGrid.hpp
        options/CallQuanto.cpp
        options/CallQuanto.hpp
        options/CallCurrency.cpp
        options/CallCurrency.hpp
        options/QuantoExchange.cpp
        options/QuantoExchange.hpp
        options/ForeignAsianOption.cpp
        options/ForeignAsianOption.hpp
        options/ForeignPerfBasket.cpp
        options/ForeignPerfBasket.hpp
        options/Option.cpp
        builders/OptionBuilder.cpp
        builders/OptionBuilder.hpp
        utils/MarketParameters.cpp
        utils/MarketParameters.hpp
        utils/FinancialInstrumentBuilder.cpp
        utils/FinancialInstrumentBuilder.hpp
        builders/TimeGridBuilder.cpp
        builders/TimeGridBuilder.hpp
        hedging_portfolio.cpp
)

# Create library
add_library(fx_hedging STATIC ${SOURCE_FILES})
target_link_libraries(fx_hedging ${PNL_LIBRARIES} nlohmann_json::nlohmann_json)

# Create test executable
add_executable(test_json_reader tests/test_json_reader.cpp)
target_link_libraries(test_json_reader fx_hedging)


add_executable(test_timegrid tests/test_timegrid.cpp utils/GridTimeGrid.cpp)
target_link_libraries(test_timegrid fx_hedging)

add_executable(test_interest_rate tests/test_interest_rate_model.cpp financial/InterestRateModel.cpp
        tests/test_currency.cpp
        tests/test_riskyasset.cpp
)
target_link_libraries(test_interest_rate fx_hedging)

add_executable(test_risky_dynamics tests/test_risky_dynamics.cpp models/RiskyDynamics.cpp)
target_link_libraries(test_risky_dynamics fx_hedging)

add_executable(test_position tests/test_position.cpp core/Position.cpp)
target_link_libraries(test_position fx_hedging)

if(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    add_definitions(-DPNL_RANGE_CHECK_OFF)
endif()

add_executable(test_currency tests/test_currency.cpp models/Currency.cpp)
target_link_libraries(test_currency fx_hedging)

add_executable(test_riskyasset tests/test_riskyasset.cpp models/RiskyDynamics.cpp)
target_link_libraries(test_riskyasset fx_hedging)

add_executable(test_global_model_init
        tests/test_global_model_init.cpp
        models/GlobalModel.cpp builders/GlobalModelBuilder.cpp models/Currency.cpp models/RiskyDynamics.cpp
        utils/GridTimeGrid.cpp
        financial/RiskyAsset.cpp financial/InterestRateModel.cpp
)
target_link_libraries(test_global_model_init fx_hedging)

add_executable(hedging_portfolio
        hedging_portfolio.cpp
        utils/json_reader.cpp utils/GridTimeGrid.cpp utils/FixedTimeGrid.cpp
        utils/MarketParameters.cpp utils/FinancialInstrumentBuilder.cpp
        core/MonteCarlo.cpp core/Position.cpp core/Portfolio.cpp
        models/GlobalModel.cpp models/RiskyDynamics.cpp models/Currency.cpp
        financial/RiskyAsset.cpp financial/InterestRateModel.cpp
        builders/GlobalModelBuilder.cpp builders/OptionBuilder.cpp builders/TimeGridBuilder.cpp
        options/CallQuanto.cpp options/CallCurrency.cpp options/QuantoExchange.cpp
        options/ForeignAsianOption.cpp options/ForeignPerfBasket.cpp options/Option.cpp

)
target_link_libraries(hedging_portfolio fx_hedging)
