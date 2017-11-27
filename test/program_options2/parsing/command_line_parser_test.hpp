/*
 * command_line_parcer_test.hpp
 *
 *  Created on: Nov 25, 2017
 *      Author: ilion
 */

#ifndef TEST_PROGRAM_OPTIONS2_PARSING_COMMAND_LINE_PARSER_TEST_HPP_
#define TEST_PROGRAM_OPTIONS2_PARSING_COMMAND_LINE_PARSER_TEST_HPP_


#include <array>
#include <experimental/array>
#include <cstddef>
#include <tuple>

#include "../../../include/io/io.hpp"
#include "../../../include/io/names.hpp"
#include "../../../include/program_options2/description.hpp"
#include "../../../include/program_options2/parsing.hpp"


namespace test {
namespace program_options2 {
namespace parsing {

using ::io::separator;
using ::io::names::complex_names;
using ::io::names::root;
using ::io::names::path;
using ::io::names::names;
using ::program_options2::description::option;
using ::program_options2::description::options_group;

struct command_line_parser_test {

    static constexpr auto test_cases = std::make_tuple(
            std::make_tuple(
                    std::experimental::make_array(
                            "path/to/executable",
                            "-h", "1"
                    )
            ),
            std::make_tuple(
                    std::experimental::make_array(
                            "path/to/executable",
                            "--help", "1"
                    )
            ),
            std::make_tuple(
                    std::experimental::make_array(
                            "path/to/executable",
                            "-v", "1"
                    )
            ),
            std::make_tuple(
                    std::experimental::make_array(
                            "path/to/executable",
                            "--version", "1"
                    )
            ),
            std::make_tuple(
                    std::experimental::make_array(
                            "path/to/executable",
                            "-h"
                    )
            ),
            std::make_tuple(
                    std::experimental::make_array(
                            "path/to/executable",
                            "--help"
                    )
            ),
            std::make_tuple(
                    std::experimental::make_array(
                            "path/to/executable",
                            "-v"
                    )
            ),
            std::make_tuple(
                    std::experimental::make_array(
                            "path/to/executable",
                            "--version"
                    )
            ),
            std::make_tuple(
                    std::experimental::make_array(
                            "path/to/executable",
                            "--precision"   , "0.05",
                            "--method"      , "ga",
                            "--max-size"    , "100000",
                            "--initial-size", "100",
                            "--crossover"   , "20",
                            "--mutation"    , "5"
                    )
            )
    );

    template<typename... Ts>
    void operator() (const std::tuple<Ts...> testCase) {
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


        using ::program_options2::parsing::command_line_parser;
        using ::program_options2::description::options;

        std::vector<std::string> args (std::get<0>(testCase).cbegin(), std::get<0>(testCase).cend());
        command_line_parser parser(options(allowed));
        auto optionRefs = parser(args);
    }

    command_line_parser_test() {
        //-- General Options --
        help.names() << names("help", "h");
        help.description() << "Produce help message";

        version.names() << names("version", "v");
        version.description() << "Prints program version";

        input.names() << names("input", "i");
        input.description() << "Input file name";

        output.names() << names("output", "o");
        output.description() << "Output file name";

        //-- Method Options --
        method.names() << names("method", "m");
        method.description() << "Method name";

        precision.names() << names("precision", "p");
        precision.description() << "Precision";

        //-- GA Options --
        gaMaxSize.names() << path().add("ga") << names("max-size");
        gaMaxSize.description() << "Population max size";

        gaInitialSize.names() << path().add("ga") << names("initial-size");
        gaInitialSize.description() << "Population initial size";

        gaCrossover.names() << path().add("ga") << names("crossover");
        gaCrossover.description() << "Number of crossover pairs in population";

        gaMutation.names() << path().add("ga") << names("mutation");
        gaMutation.description() << "Number of mutated individuals in population";

        //-- CMN-GA Options --
        cmngaMaxSize.names() << path().add("cmn-ga") << names("max-size");
        cmngaMaxSize.description() << "Population max size";

        cmngaInitialSize.names() << path().add("cmn-ga") << names("initial-size");
        cmngaInitialSize.description() << "Population initial size";

        cmngaCrossover.names() << path().add("cmn-ga") << names("crossover");
        cmngaCrossover.description() << "Number of crossover pairs in population";

        cmngaMutation.names() << path().add("cmn-ga") << names("mutation");
        cmngaMutation.description() << "Number of mutated individuals in population";

        cmngaNearest.names() << path().add("cmn-ga") << names("nearest");
        cmngaNearest.description() << "Number of nearest individuals individual must be more fit to be local optima";

        cmngaCrowd.names() << path().add("cmn-ga") << names("crowd");
        cmngaCrowd.description() << "Number of individuals to choose from for mating for crossover";

        cmngaCrossoverTries.names() << path().add("cmn-ga") << names("crossover-tries");
        cmngaCrossoverTries.description() << "Number of tries to perform all crossovers";

        cmngaMutationTries.names() << path().add("cmn-ga") << names("mutation-tries");
        cmngaMutationTries.description() << "Number of tries to perform all mutations";
    }

protected:
    option<bool> help;
    option<bool> version;
    option<std::string> input;
    option<std::string> output;
    option<std::string> method;
    option<double> precision;

    option<std::size_t> gaMaxSize;
    option<std::size_t> gaInitialSize;
    option<std::size_t> gaCrossover;
    option<std::size_t> gaMutation;

    option<std::size_t> cmngaMaxSize;
    option<std::size_t> cmngaInitialSize;
    option<std::size_t> cmngaCrossover;
    option<std::size_t> cmngaMutation;
    option<std::size_t> cmngaNearest;
    option<std::size_t> cmngaCrowd;
    option<std::size_t> cmngaCrossoverTries;
    option<std::size_t> cmngaMutationTries;
};

constexpr decltype(command_line_parser_test::test_cases) command_line_parser_test::test_cases;

}   //-- namespace parsing --
}   //-- namespace program_options2 --
}   //-- namespace test --


#endif /* TEST_PROGRAM_OPTIONS2_PARSING_COMMAND_LINE_PARSER_TEST_HPP_ */
