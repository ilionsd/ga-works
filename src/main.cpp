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

#include "options/description.hpp"


#include "../test/test.hpp"


namespace po = ::boost::program_options;


constexpr double version = 0.15;


po::options_description
config_options(const std::string&, const po::options_description&);
void work(const genetic_algorithm::cmn_ga::cmn_ga::parameters&);
void parse_options(int argc, char** argv);

auto main(int argc, char* argv[]) -> int {

    ::test::testing();

    parse_options(argc, argv);

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

void parse_options(int argc, char** argv) {

//    auto allowed = po::options_description("Allowed options")
//        .add(options::description::general)
//        .add(options::description::io)
//        .add(options::description::algorithm)
//        .add(options::description::ga)
//        .add(options::description::cmnga);
//
//    auto positional = po::positional_options_description()
//        .add(options::algorithm::method.c_str(), 1);
//
//    po::variables_map vm;
//    po::store(po::command_line_parser(argc, argv).options(allowed).positional(positional).run(), vm);
//    po::notify(vm);
//
//    using std::cout;
//    using std::endl;
//    if ( vm.count(options::general::version) )
//        cout << "Genetic algorithm optimizing program GA-Works. v" << version << endl;
//    else {
//        if ( vm.count(options::algorithm::method) ) {
//            std::string methodName = vm[options::algorithm::method].as<std::string>();
//            if ( vm.count(options::general::help) ) {
//                cout << "cmn_ga-rework " + methodName + " [" + methodName + " OPTIONS]" << endl;
//                cout << "There will be method help soon..." << endl;
//            }
//            else {
//                genetic_algorithm::cmn_ga::cmn_ga::parameters params;
//                if ( vm.count(options::io::input) ) {
//                    /*
//                     * To Do
//                     * Read config file to get method arguments --
//                     * and merge with arguments that may be passed from console.
//                     */
//                }
//            }
//        }
//        else if ( vm.count(options::general::help) ) {
//            cout << "cmn_ga-rework <METHOD> [OTHER OPTIONS]" << endl;
//            cout << options::description::general << endl;
//            cout << options::description::io << endl;
//            cout << options::description::algorithm << endl;
//        }
//    }

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
