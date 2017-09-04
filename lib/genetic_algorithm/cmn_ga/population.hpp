/*
 * population.hpp
 *
 *  Created on: Aug 17, 2017
 *      Author: ilion
 */

#ifndef LIB_GENETIC_ALGORITHM_CMN_GA_POPULATION_HPP_
#define LIB_GENETIC_ALGORITHM_CMN_GA_POPULATION_HPP_


#include <cstddef>
#include <valarray>
#include <vector>


namespace genetic_algorithm {
namespace cmn_ga {

template<typename T>
class population {
    typedef T value_type;
    typedef std::size_t size_type;
    typedef std::valarray<value_type> point_type;

    inline auto operator() (const size_type index) -> point_type& {
        return mPopulation[index];
    }
    inline auto operator() (const size_type index) const -> const point_type& {
        return mPopulation[index];
    }

    inline size_type size() const {
        return mPopulation.size();
    }

private:
    std::vector<point_type> mPopulation;

};  //-- class population --

}   //-- namespace cmn_ga --
}   //-- namespace genetic_algorithm --


#endif /* LIB_GENETIC_ALGORITHM_CMN_GA_POPULATION_HPP_ */
