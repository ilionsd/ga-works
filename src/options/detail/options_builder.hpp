/*
 * description_builder.hpp
 *
 *  Created on: Sep 7, 2017
 *      Author: ilion
 */

#ifndef SRC_OPTIONS_DETAIL_OPTIONS_BUILDER_HPP_
#define SRC_OPTIONS_DETAIL_OPTIONS_BUILDER_HPP_


#include <string>

#include <boost/program_options.hpp>



namespace options {
namespace detail {

class options_builder {
public:
    typedef options_builder self_type;

    inline
    options_builder(const std::string& caption) :
        mOptions(caption)
    {}

    inline
    ::boost::program_options::options_description&
    options() {
        return mOptions;
    }
    inline
    const ::boost::program_options::options_description&
    options() const {
        return mOptions;
    }
    inline
    ::boost::program_options::options_description
    build() const {
        return mOptions;
    }

    inline self_type& add_options(const ::boost::program_options::options_description& options) {
        this->options().add(options);
        return *this;
    }
    inline self_type& add_option(const ::boost::program_options::option_description& option) {
        this->options().add_options();
    }

private:
    ::boost::program_options::options_description mOptions;
};

}   //-- namespace detail --
}   //-- namespace options --


#endif /* SRC_OPTIONS_DETAIL_OPTIONS_BUILDER_HPP_ */
