/*
 * proximity.hpp
 *
 *  Created on: Aug 17, 2017
 *      Author: ilion
 */

#ifndef LIB_GENETIC_ALGORITHM_CMN_GA_PROXIMITY_HPP_
#define LIB_GENETIC_ALGORITHM_CMN_GA_PROXIMITY_HPP_


#include <cstddef>
#include <cassert>
#include <limits>
#include <vector>
#include <functional>
#include <utility>


#include "../../../include/fn/math.hpp"
#include "../../../include/fn/math_v.hpp"
#include "population.hpp"

namespace genetic_algorithm {
namespace cmn_ga {

template<typename T>
struct euclidean_distance {
    typedef T value_type;

    inline constexpr auto operator() (
            const std::valarray<value_type>& a,
            const std::valarray<value_type>& b) const
    -> value_type {
        namespace math = ::fn::math;
        return math::sqrt<value_type>()( math::square_v<value_type>()(a - b).sum() );
    }
};

template<typename T, class V = std::valarray<T>>
class proximity_matrix {
public:
    typedef T value_type;
    typedef std::size_t size_type;
    typedef V vector_type;

    static constexpr value_type infinite_proximity = std::numeric_limits<value_type>::infinity();

    proximity_matrix() :
        mSize(0),
        mMatrix(0)
    {}
    proximity_matrix(const size_type size) :
        mSize(0),
        mMatrix( size )
    {}

    inline size_type size() const {
        return mSize;
    }
    inline size_type capacity() const {
        return mMatrix.size();
    }
    inline void reserve(const size_type size) {
        mMatrix.resize(size);
        mSize = std::min(mSize, size);
    }

    inline value_type operator() (size_type i, size_type j) const {
        if (i == j)
            return infinite_proximity;
        else if (i < j)
            std::swap(i, j);
        return mMatrix[i][j];
    }

    vector_type vector(const size_type k, bool includeSelf = true) const {
        vector_type proximitiesVector (mSize);
        for (size_type j = 0; j < k; ++j)
            proximitiesVector[j] = mMatrix[k][j];
        if (includeSelf)
            proximitiesVector[k] = infinite_proximity;
        for (size_type i = k + 1; i < mSize; ++i)
            proximitiesVector[i] = mMatrix[i][k];
        return proximitiesVector;
    }

    void add_vector(vector_type&& proximities) {
        assert(mSize == proximities.size());
        mMatrix[mSize + 1] = std::move(proximities);
        ++mSize;
    }

private:
    size_type mSize;
    std::vector<vector_type> mMatrix;
};

}   //-- namespace cmn_ga --
}   //-- namespace genetic_algorithm --


#endif /* LIB_GENETIC_ALGORITHM_CMN_GA_PROXIMITY_HPP_ */
