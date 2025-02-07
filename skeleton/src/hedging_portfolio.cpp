//
// Created by Aymane on 06/02/2025.
//

#include <fstream>
#include <iostream>
#include <ostream>
#include <nlohmann/json.hpp>
#include <pnl/pnl_matrix.h>
#include <pnl/pnl_random.h>

#include "builders/GlobalModelBuilder.hpp"
#include "builders/OptionBuilder.hpp"
#include "builders/TimeGridBuilder.hpp"
#include "core/montecarlo.hpp"
#include "models/GlobalModel.hpp"
#include "options/Option.hpp"
#include "core/Portfolio.hpp"

void printUsage(const char* programName)
{
    std::cerr << "Usage: " << programName << " <params.json> <market.csv> <output.json>" << std::endl;
}

int main(int argc, char** argv)
{
    if (argc != 4)
    {
        printUsage(argv[0]);
        return 1;
    }

    try
    {
        char* paramsFile = argv[1];
        char* marketDataFile = argv[2];
        char* outputFile = argv[3];

        std::ifstream paramsFileStream(paramsFile);
        if (!paramsFileStream)
            throw std::runtime_error("hedging_portfolio: cannot open paramsFile" + std::string(paramsFile));

        nlohmann::json params = nlohmann::json::parse(paramsFileStream);
        PnlMat* marketData = pnl_mat_create_from_file(marketDataFile);

        GlobalModel* model = GlobalModelBuilder::createFromJson(params);
        Option* option = OptionBuilder::createFromJson(params);

        int nbSamples = params["SampleNb"].get<int>();
        double fdStep = params["RelativeFiniteDifferenceStep"].get<double>();

        // Set up the Montecarlo simulation
        MonteCarlo montecarlo(option, *model, nbSamples, fdStep);
        // Set up the rebalancing time grid
        ITimeGrid* rebalancingGrid = TimeGridBuilder::createRebalancingFromJson(params);
        // Set up the portfolio
        Portfolio portfolio(montecarlo, rebalancingGrid, marketData);
        // Initializing random number generator
        PnlRng* rng = pnl_rng_create(PNL_RNG_MERSENNE);
        pnl_rng_sseed(rng, time(NULL));

        // Run the simulation
        portfolio.simulateRebalancing(marketData, rng);

        std::ofstream outStream(outputFile);
        if (!outStream)
            throw std::runtime_error("hedging_portfolio: cannot open outputFile" + std::string(outputFile));

        // Write results to output file
        std::ofstream ifout(argv[3], std::ios_base::out);
        if (!ifout.is_open()) {
            std::cout << "Unable to open file " << argv[3] << std::endl;
            std::exit(1);
        }
        nlohmann::json jsonPortfolio = portfolio.getPositions();
        ifout << jsonPortfolio.dump(4);
        ifout.close();

        pnl_rng_free(&rng);
        pnl_mat_free(&marketData);
        delete model;
        delete option;
        delete rebalancingGrid;

        std::cout << "Hedging simulation completed successfully" << std::endl;
        std::cout << "Results written to: " << argv[3] << std::endl;

        return 0;
    } catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

}


