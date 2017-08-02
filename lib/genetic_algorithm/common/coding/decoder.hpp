/*
 * decoder.hpp
 *
 *  Created on: Aug 1, 2017
 *      Author: ilion
 */

#ifndef LIB_GENETIC_ALGORITHM_COMMON_CODING_DECODER_HPP_
#define LIB_GENETIC_ALGORITHM_COMMON_CODING_DECODER_HPP_


namespace genetic_algorithm {
namespace common {
namespace coding {

template<typename T>
struct decoder {
    typedef T coder_type;
    typedef typename coder_type::array_src_type array_src_type;
    typedef typename coder_type::array_dst_type array_dst_type;

    inline constexpr decoder(const coder_type& coder) :
            coder(coder)
    {}
    template<typename... Ts>
    inline constexpr decoder(const Ts&... args) :
            coder( args... )
    {}

    inline constexpr array_src_type operator() (const array_dst_type& array) const {
        return coder.decode(array);
    }

    const coder_type& coder;
};

}   //-- namespace coding --
}   //-- namespace common --
}   //-- namespace coding --


#endif /* LIB_GENETIC_ALGORITHM_COMMON_CODING_DECODER_HPP_ */
