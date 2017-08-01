/*
 * main.cpp
 *
 *  Created on: Jul 14, 2017
 *      Author: ilion
 */

#include <iostream>

#include "../lib/genetic_algorithm/common/generating/uniform_generator.hpp"
#include "../lib/genetic_algorithm/common/coding/numeric_coder.hpp"

#include "../test/test.hpp"
#include "../test/genetic_algorithm/common/generating/uniform_generator_test.hpp"
#include "../test/genetic_algorithm/common/coding/numeric_coder_test.hpp"



void testing();

auto main(int argc, char** argv) -> int {

    testing();


    return 0;
}

void testing() {
    using std::cout;
    using std::endl;

#ifndef NDEBUG

    cout << "Debug build" << endl;

    TEST_RUN_ALL( ::genetic_algorithm::common::generating::uniform_generator )
    TEST_RUN_ALL( ::genetic_algorithm::common::coding::numeric_coder )

#endif

};
