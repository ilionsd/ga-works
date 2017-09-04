/*
 * fitness.hpp
 *
 *  Created on: Aug 17, 2017
 *      Author: ilion
 */

#ifndef LIB_GENETIC_ALGORITHM_CMN_GA_FITNESS_HPP_
#define LIB_GENETIC_ALGORITHM_CMN_GA_FITNESS_HPP_


#include <cstddef>
#include <valarray>
#include <functional>


namespace genetic_algorithm {
namespace cmn_ga {

template<typename T>
class fitness {
    typedef T value_type;
    typedef std::size_t size_type;

    template<class T>
    inline auto operator() (const T& index) {
        return mFitness[index];
    }
    template<class T>
    inline auto operator() (const T& index) const {
        return mFitness[index];
    }
    std::valarray<value_type> scale(const std::valarray<size_type>& localOptimas) const {

    }

private:
    std::valarray<value_type> mFitness;
    std::function<value_type(std::valarray<value_type>)> mFitnessF;
};  //-- class fitness --

}   //-- namespace cmn_ga --
}   //-- namespace genetic_algotithm --


#endif /* LIB_GENETIC_ALGORITHM_CMN_GA_FITNESS_HPP_ */
