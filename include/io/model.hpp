/*
 * model.hpp
 *
 *  Created on: Sep 21, 2017
 *      Author: ilion
 */

#ifndef INCLUDE_IO_MODEL_HPP_
#define INCLUDE_IO_MODEL_HPP_


#include "../../lib/io/model/concept.hpp"
#include "../../lib/io/model/model.hpp"


namespace io {
namespace model {

template<typename CharT> class basic_concept;
using  concept = basic_concept<char>;
using wconcept = basic_concept<wchar_t>;

template<typename CharT, class T> class basic_model;
template<typename T> using  model = basic_model<char, T>;
template<typename T> using wmodel = basic_model<wchar_t, T>;

}   //-- namespace model --
}   //-- namespace io --


#endif /* INCLUDE_IO_MODEL_HPP_ */
