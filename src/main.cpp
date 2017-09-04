/*
 * main.cpp
 *
 *  Created on: Jul 14, 2017
 *      Author: ilion
 */

#define _USE_MATH_DEFINES

#include <cstddef>
#include <cmath>
#include <valarray>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

#include <boost/program_options.hpp>

#include "../include/fn/math.hpp"
#include "../lib/io/out.hpp"
#include "../lib/utility/valarray.hpp"
#include "../lib/genetic_algorithm/common/space.hpp"
#include "../lib/genetic_algorithm/cmn_ga/cmn_ga.hpp"


#include "../test/test.hpp"


namespace po = ::boost::program_options;


constexpr double version = 0.15;

struct option {
static const std::string
    help,
    version,
    input,
    output,
    method,
    precision;
};
const std::string option::help      = "help";
const std::string option::version   = "version";
const std::string option::input     = "input";
const std::string option::output    = "output";
const std::string option::method    = "method";
const std::string option::precision = "precision";


struct method {
    static const std::string ga;
    static const std::string cmn_ga;

    static const std::vector<std::string> options;
};
const std::string method::ga = "GA";
const std::string method::cmn_ga = "CMN-GA";

const std::vector<std::string> method::options {
    method::ga,
    method::cmn_ga
};

struct cmn_ga {
    static const std::string
    max_size,
    initial_size,
    crossover,
    mutation,
    nearest,
    crowd,
    crossover_tries,
    mutation_tries;

    static const std::vector<std::string> options;
};
const std::string cmn_ga::max_size = "max-size";
const std::string cmn_ga::initial_size = "initial-size";
const std::string cmn_ga::crossover = "crossover";
const std::string cmn_ga::mutation = "mutation";
const std::string cmn_ga::nearest = "nearest";
const std::string cmn_ga::crowd = "crowd";
const std::string cmn_ga::crossover_tries = "crossover-tries";
const std::string cmn_ga::mutation_tries = "mutation-tries";

const std::vector<std::string> cmn_ga::options {
    cmn_ga::max_size,
    cmn_ga::initial_size,
    cmn_ga::crossover,
    cmn_ga::mutation,
    cmn_ga::nearest,
    cmn_ga::crowd,
    cmn_ga::crossover_tries,
    cmn_ga::mutation_tries
};

const std::unordered_map<std::string, std::vector<std::string>> method_options {
    { method::cmn_ga, cmn_ga::options }
};


po::options_description
config_options(const std::string&, const po::options_description&);

void work(const genetic_algorithm::cmn_ga::cmn_ga::parameters&);

auto main(int argc, char** argv) -> int {

    ::test::testing();

    po::options_description general("General options");
    general.add_options()
            ( (option::help    + ",h").c_str(), "Produce a help message" )
            ( (option::version + ",v").c_str(), "Outputs program version");

    po::options_description io("Input/Output options");
    io.add_options()
            ( (option::input  + ",i").c_str(), po::value<std::string>(), "Input file" )
            ( (option::output + ",o").c_str(), po::value<std::string>(), "Output file");

    std::stringstream ss;
    ss << "Methods:" << std::endl;
    ss << "CMN-GA: \t";
    ss << "Cumulative Multi-Niching Genetic Algorithm for multimodal function optimization." << std::endl;

    po::options_description algorithm("Algorithm options");
    algorithm.add_options()
            ( (option::method    + ",m").c_str(), po::value<std::string>(), ss.str().c_str())
            ( (option::precision + ",p").c_str(), po::value<double>()     , "Precision"     );
    po::positional_options_description positional;
    positional.add(option::method.c_str(), 1);

    std::unordered_map<std::string, po::options_description> algorithmSpecific;
    po::options_description cmn_gaOptions("CMN-GA options");
    cmn_gaOptions.add_options()
            (cmn_ga::max_size    .c_str(), po::value<std::size_t>(), "Max population size")
            (cmn_ga::initial_size.c_str(), po::value<std::size_t>(), "Initial population size")
            (cmn_ga::crossover.c_str(), po::value<std::string>(), "Crossover pairs number")
            (cmn_ga::mutation .c_str(), po::value<std::string>(), "Mutated individuals number")
            (cmn_ga::nearest  .c_str(), po::value<std::string>(), "Nearest individuals number for optima criteria")
            (cmn_ga::crowd    .c_str(), po::value<std::string>(), "Number of individuals for proximity based selection")
            (cmn_ga::crossover_tries.c_str(), po::value<std::string>(), "Number of attempts to perform crossovers")
            (cmn_ga::mutation_tries .c_str(), po::value<std::string>(), "Number of attempts to perform mutations");

    algorithmSpecific.insert({method::cmn_ga, cmn_gaOptions});

    po::options_description visible("Allowed options");
    visible.add(general).add(io).add(algorithm).add(cmn_gaOptions);

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(visible).positional(positional).run(), vm);
    po::notify(vm);

    using std::cout;
    using std::endl;
    if ( vm.count(option::version) )
        cout << "Genetic algorithm optimizing program GA-Works. v" << version << endl;
    else {
        if ( vm.count(option::method) ) {
            std::string methodName = vm[option::method].as<std::string>();
            if ( vm.count(option::help) ) {
                cout << "cmn_ga-rework " + methodName + " [" + methodName + " OPTIONS]" << endl;
                cout << cmn_gaOptions << endl;
            }
            else {
                genetic_algorithm::cmn_ga::cmn_ga::parameters params;
                if ( vm.count(option::input) ) {
                    std::string configFile = vm[option::input].as<std::string>();
                    po::options_description configOptions = config_options(methodName, cmn_gaOptions);
                    po::variables_map cfgvm;
                    po::store(po::parse_config_file<char>(configFile.c_str(), configOptions, true), cfgvm);
                    po::notify(cfgvm);
                }

            }
        }
        else if ( vm.count(option::help) ) {
            cout << "cmn_ga-rework <METHOD> [OTHER OPTIONS]" << endl;
            cout << general << endl;
            cout << algorithm << endl;
        }
    }

    return 0;
}

po::options_description
config_options(const std::string& methodName, const po::options_description& commandLineOptions) {
    po::options_description cfgFileOptions( ("Config file " + methodName + " options").c_str() );
    for (std::size_t k = 0; k < commandLineOptions.options().size(); ++k) {
        cfgFileOptions.add_options()(
                (methodName + "." + commandLineOptions.options()[k]->long_name()).c_str(),
                commandLineOptions.options()[k]->semantic().get());
    }
    return cfgFileOptions;
}

po::variables_map
map_variables(
        const std::unordered_map<std::string, std::string>&mapping,
        const po::variables_map& srcKey,
        const po::variables_map& srcVal) {
    po::variables_map mapped;

    for (const auto& kv : mapping) {
        const auto& key = kv.first;
        const auto& val = kv.second;
        if ( !srcVal[val].empty() )
            mapped.insert({ val, srcVal[val] });
        if ( !srcKey[key].empty() )
            mapped.insert({ val, srcKey[key] });
    }

    return mapped;
}

void work(const genetic_algorithm::cmn_ga::cmn_ga::parameters& params) {
    namespace math = ::fn::math;

    std::function<double(double)> f1 = [](double x)
            -> double { return math::power<double>()(math::sin<double>()(5.1 * M_PI * x + 0.5), 6.0); };

    std::function<double(double)> f2 = [f1](double x)
            -> double { return math::exp<double>()(-4.0 * math::ln<double>()(2.0) * math::power<double>()(x - 0.0667, 2.0) / 0.64) * f1(x); };

    std::valarray<double> peaks = {-32, -16, 0, 16, 32};
    std::function<double(double, double)> f3 = [&peaks](double x, double y) -> double {
        double sum = 0.0;
        for (std::size_t i = 0; i < peaks.size(); ++i)
            for (std::size_t j = 0; j < peaks.size(); ++j)
                sum += 1.0 / (i + j + math::power<double>()(x - peaks[i], 6.0) + math::power<double>()(y - peaks[j], 6.0));
        return 0.002 + sum;
    };

    std::valarray<double>
        a = {-20.0 ,  -5.0,  0.0 , 30.0,  30.0 },
        b = {-20.0 , -25.0, 30.0 ,  0.0, -30.0 },
        h = {  0.4 ,   0.2,  0.7 ,  1.0,   0.05},
        w = {  0.02,   0.5,  0.01,  2.0,   0.1 };
    std::function<double(double, double)> f4 = [&a, &b, &h, &w](double x, double y) -> double {
        double sum = 0;
        for (std::size_t k = 0; k < a.size(); ++k)
            sum += h[k] / (1.0 + w[k] * (math::power<double>()(x - a[k], 2.0) + math::power<double>()(y - b[k], 2.0)));
        return sum;
    };

    auto fs = std::make_tuple(f1, f2, f3, f4);
    auto realSpaces = std::make_tuple(
            genetic_algorithm::common::make_space_real(1, 0.0, 1.0),
            genetic_algorithm::common::make_space_real(1, 0.0, 1.0),
            genetic_algorithm::common::make_space_real(2, -40.0, 40.0),
            genetic_algorithm::common::make_space_real(2, -40.0, 40.0)
    );

    const std::size_t spaceSize = 3;
    const double realLeftBound = -1, realRightBound = 1;
    auto realSpace = ::genetic_algorithm::common::make_space_real(spaceSize, realLeftBound, realRightBound);

    std::function<double(std::valarray<double>)> f = [](const std::valarray<double> x)
            -> double { return -x[0]*x[0] - x[1]*x[1] - x[2] * x[2]; };

    genetic_algorithm::cmn_ga::cmn_ga alg ( params, realSpace, f );
    alg.init();
    auto optimas = alg();
    {
        using namespace io;
        std::cout << "Optimas number: " << optimas.size() << std::endl;
        std::cout << optimas << std::endl;
    }
}
