/*
 * io_model.hpp
 *
 *  Created on: Aug 22, 2017
 *      Author: ilion
 */

#ifndef LIB_IO_IO_MODEL_HPP_
#define LIB_IO_IO_MODEL_HPP_


namespace io {

template<typename T>
class io_model {
    typedef T value_type;


private:
    value_type mVal;
};

}   //-- namespace io --


#endif /* LIB_IO_IO_MODEL_HPP_ */
