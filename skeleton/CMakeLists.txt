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

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PNL_INCLUDE_DIRS})

# Add source files
set(SOURCE_FILES
        src/utils/json_reader.cpp
        src/utils/json_reader.hpp
        src/core/MonteCarlo.hpp
        src/core/MonteCarlo.cpp
        src/core/Position.hpp
        src/core/Position.cpp
        src/models/GlobalModel.cpp
        src/models/GlobalModel.hpp
        src/models/RiskyDynamics.cpp
        src/models/RiskyDynamics.hpp
        src/models/Currency.cpp
        src/models/Currency.hpp
        src/financial/Option.cpp
        src/financial/Option.hpp
        src/financial/RiskyAsset.cpp
        src/financial/RiskyAsset.hpp
        src/financial/InterestRateModel.cpp
        src/financial/InterestRateModel.hpp
        src/utils/TimeGrid.cpp
        src/utils/TimeGrid.hpp
        src/test.cpp
)

# Create library
add_library(fx_hedging STATIC ${SOURCE_FILES})
target_link_libraries(fx_hedging ${PNL_LIBRARIES} nlohmann_json::nlohmann_json)

# Create test executable
add_executable(test_json_reader src/tests/test_json_reader.cpp
        src/tests/test_timegrid.cpp
        src/tests/test_currency.cpp)
target_link_libraries(test_json_reader fx_hedging)

add_executable(test src/test.cpp)
target_link_libraries(test fx_hedging)

add_executable(test_timegrid src/tests/test_timegrid.cpp src/utils/TimeGrid.cpp)
target_link_libraries(test_timegrid fx_hedging)

add_executable(test_currency src/tests/test_currency.cpp src/models/Currency.cpp)
target_link_libraries(test_currency fx_hedging)


if(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    add_definitions(-DPNL_RANGE_CHECK_OFF)
endif()
add_executable(test_interest_rate src/tests/test_interest_rate_model.cpp src/financial/InterestRateModel.cpp)
