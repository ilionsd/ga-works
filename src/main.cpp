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

#include "../include/fn/math.hpp"
#include "../include/io/io.hpp"
#include "../include/io/names.hpp"
#include "../include/program_options2/description.hpp"
#include "../include/program_options2/parsing.hpp"
#include "../lib/utility/valarray.hpp"
#include "../lib/io/utility/vector_join.hpp"
#include "../lib/genetic_algorithm/common/space.hpp"
#include "../lib/genetic_algorithm/cmn_ga/cmn_ga.hpp"

#include "../test/test.hpp"


constexpr double version = 0.15;


void work(const genetic_algorithm::cmn_ga::cmn_ga::parameters&);

auto main(int argc, char* argv[]) -> int {

    ::test::testing();

    using ::io::names::root;
    using ::io::names::path;
    using ::io::names::names;
    using ::program_options2::description::option;
    using ::program_options2::description::options_group;

    //-- General Options --
    option<void> help;
    help.names() << names("help", "h");
    help.description() << "Produce help message";

    option<void> version;
    version.names() << names("version", "v");
    version.description() << "Prints program version";

    option<std::string> input;
    input.names() << names("input", "i");
    input.description() << "Input file name";

    option<std::string> output;
    output.names() << names("output", "o");
    output.description() << "Output file name";

    //-- Method Options --
    option<std::string> method;
    method.names() << names("method", "m");
    method.description() << "Method name";

    option<double> precision;
    precision.names() << names("precision", "p");
    precision.description() << "Precision";

    //-- GA Options --
    option<std::size_t> gaMaxSize;
    gaMaxSize.names() << path().add("ga") << names("max-size");
    gaMaxSize.description() << "Population max size";

    option<std::size_t> gaInitialSize;
    gaInitialSize.names() << path().add("ga") << names("initial-size");
    gaInitialSize.description() << "Population initial size";

    option<std::size_t> gaCrossover;
    gaCrossover.names() << path().add("ga") << names("crossover");
    gaCrossover.description() << "Number of crossover pairs in population";

    option<std::size_t> gaMutation;
    gaMutation.names() << path().add("ga") << names("mutation");
    gaMutation.description() << "Number of mutated individuals in population";

    //-- CMN-GA Options --
    option<std::size_t> cmngaMaxSize;
    cmngaMaxSize.names() << path().add("cmn-ga") << names("max-size");
    cmngaMaxSize.description() << "Population max size";

    option<std::size_t> cmngaInitialSize;
    cmngaInitialSize.names() << path().add("cmn-ga") << names("initial-size");
    cmngaInitialSize.description() << "Population initial size";

    option<std::size_t> cmngaCrossover;
    cmngaCrossover.names() << path().add("cmn-ga") << names("crossover");
    cmngaCrossover.description() << "Number of crossover pairs in population";

    option<std::size_t> cmngaMutation;
    cmngaMutation.names() << path().add("cmn-ga") << names("mutation");
    cmngaMutation.description() << "Number of mutated individuals in population";

    option<std::size_t> cmngaNearest;
    cmngaNearest.names() << path().add("cmn-ga") << names("nearest");
    cmngaNearest.description() << "Number of nearest individuals individual must be more fit to be local optima";

    option<std::size_t> cmngaCrowd;
    cmngaCrowd.names() << path().add("cmn-ga") << names("crowd");
    cmngaCrowd.description() << "Number of individuals to choose from for mating for crossover";

    option<std::size_t> cmngaCrossoverTries;
    cmngaCrossoverTries.names() << path().add("cmn-ga") << names("crossover-tries");
    cmngaCrossoverTries.description() << "Number of tries to perform all crossovers";

    option<std::size_t> cmngaMutationTries;
    cmngaMutationTries.names() << path().add("cmn-ga") << names("mutation-tries");
    cmngaMutationTries.description() << "Number of tries to perform all mutations";


    options_group io("I/O Options");
    io << input << output;

    options_group general("General Options");
    general << help << version << io << method << precision;

    options_group ga("GA Options");
    ga << gaMaxSize << gaInitialSize << gaCrossover << gaMutation;

    options_group cmnga("CMN-GA Options");
    cmnga << cmngaMaxSize << cmngaInitialSize
            << cmngaCrossover << cmngaMutation
            << cmngaNearest << cmngaCrowd
            << cmngaCrossoverTries << cmngaMutationTries;

    options_group allowed("Allowed Options");
    allowed << general << ga << cmnga;

    ::program_options2::parsing::command_line_parser parser(::program_options2::description::options(general));
    ::program_options2::parsing::parse_command_line(parser, static_cast<std::size_t>(argc), argv);

    return 0;
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
        using namespace std::string_literals;
        std::cout << "Optimas number: " << optimas.size() << std::endl;
        for (const auto& optima : optimas)
            std::cout << ::io::utility::vector_join(optima, static_cast<std::string>(separator::coma)) << std::endl;
    }
}
