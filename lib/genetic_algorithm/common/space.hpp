/*
 * space.hpp
 *
 *  Created on: Aug 7, 2017
 *      Author: ilion
 */

#ifndef LIB_GENETIC_ALGORITHM_COMMON_SPACE_HPP_
#define LIB_GENETIC_ALGORITHM_COMMON_SPACE_HPP_


#include <cstddef>
#include <cassert>
#include <valarray>


#include "../../types/primitive.hpp"


namespace genetic_algorithm {
namespace common {

template<class T>
class space {
public:
    typedef std::size_t size_type;
    typedef T value_type;
    typedef std::valarray<value_type> vector_type;

    inline constexpr space(const vector_type& leftBounds, const vector_type& rightBounds) :
        mSize (leftBounds.size()),
        mLeftBounds (leftBounds),
        mRightBounds (rightBounds)
    {
        assert(leftBounds.size() == rightBounds.size());
    }
    inline constexpr space(const space<value_type>& other) :
            mSize (other.mSize),
            mLeftBounds (other.mLeftBounds),
            mRightBounds (other.mRightBounds)
    {}

    inline constexpr size_type size() const {
        return mSize;
    }
    inline constexpr const vector_type&  left_bounds() const {
        return mLeftBounds;
    }
    inline constexpr const vector_type& right_bounds() const {
        return mRightBounds;
    }
    inline bool is_in(const vector_type& vec) const {
        return (left_bounds() <= vec && vec <= right_bounds()).min();
    }

private:
    size_type mSize;
    vector_type mLeftBounds, mRightBounds;
};


template<typename T = double>
using real_space = space<types::real_t<T>>;

template<typename T>
using uint_space = space<types::unsigned_integer_t<T>>;


template<typename T>
inline auto make_space(const std::valarray<T>& leftBounds, const std::valarray<T>& rightBounds) -> space<T> {
    return space<T>(leftBounds, rightBounds);
}
template<typename T>
inline auto make_space(const std::size_t spaceSize, const T leftBound, const T rightBound) -> space<T> {
    return make_space(utility::valarray::repeat(spaceSize, leftBound),
            utility::valarray::repeat(spaceSize, rightBound));
}

template<typename T>
inline auto make_space_real(const std::valarray<T>& leftBounds, const std::valarray<T>& rightBounds) -> real_space<T> {
    return real_space<T>(leftBounds, rightBounds);
}
template<typename T>
inline auto make_space_real(const std::size_t spaceSize, const T leftBound, const T rightBound) -> real_space<T> {
    return make_space_real(utility::valarray::repeat(spaceSize, leftBound),
            utility::valarray::repeat(spaceSize, rightBound));
}

template<typename T>
inline auto make_space_uint(const std::valarray<T>& rightBounds) -> uint_space<T> {
    std::valarray<T> leftBounds (T(0), rightBounds.size());
    return uint_space<T>(leftBounds, rightBounds);
}
template<typename T>
inline auto make_space_uint(const std::size_t spaceSize, const T leftBound, const T rightBound) -> uint_space<T> {
    return make_space_uint(utility::valarray::repeat(spaceSize, leftBound),
            utility::valarray::repeat(spaceSize, rightBound));
}

template<typename T>
inline auto make_space_uint_from_gene_sizes(const std::valarray<std::size_t>& geneSizes) -> uint_space<T>{
    std::valarray<T> rightBounds = utility::valarray::convert_to<T>((1ul << geneSizes) - 1ul);
    return make_space_uint(rightBounds);
}
template<typename T>
inline auto make_space_uint_from_gene_sizes(const std::size_t spaceSize, const std::size_t geneSize) -> uint_space<T> {
    return make_space_uint_from_gene_sizes<T>(utility::valarray::repeat(spaceSize, geneSize));
}


}   //-- namespace common --
}   //-- namespace genetic_algorithm --


#endif /* LIB_GENETIC_ALGORITHM_COMMON_SPACE_HPP_ */
