/*
 * tuple.hpp
 *
 *  Created on: Jul 21, 2017
 *      Author: ilion
 */

#ifndef LIB_UTILITY_TUPLE_HPP_
#define LIB_UTILITY_TUPLE_HPP_

#include <tuple>
#include <utility>


namespace utility {
namespace tuple {

namespace detail {


template<typename F, typename... Ts, std::size_t... I>
constexpr void for_each_impl(const F& func, const std::tuple<Ts...>& tuple, std::index_sequence<I...>) {
    auto l = { ( func(std::get<I>(tuple)), 0 )... };
};


};  //-- namespace detail --


template<typename F, typename... Ts, typename Indices = std::make_index_sequence<sizeof...(Ts)>>
constexpr void for_each(const F& func, const std::tuple<Ts...>& tuple) {
    detail::for_each_impl(func, tuple, Indices{});
};


template<typename T, typename... Ts>
T from_tuple(const std::tuple<Ts...>& args) {

}



template<typename... Ts>
class stack {
public:
    typedef std::tuple<Ts&...> tuple_type;
    static constexpr std::size_t size = sizeof...(Ts);

    inline constexpr stack(const Ts... args) :
        mTuple { args... }
    {};

    inline constexpr bool empty() const {
        return !size;
    };

    inline constexpr const auto& top() const {
        return std::get<size - 1>(mTuple);
    };
    inline constexpr auto& top() {
        return std::get<size - 1>(mTuple);
    };

    inline constexpr auto pop() const {
        return stack { pop_impl(std::make_index_sequence<size - 1>{}) };
    };

    template<typename T>
    inline constexpr auto push(const T val) const {
        return stack { push_impl(val, std::make_index_sequence<size>{}) };
    };


private:
    template<std::size_t... I>
    inline constexpr auto pop_impl(std::index_sequence<I...>) const {
        return std::make_tuple( std::get<I>(mTuple)... );
    };
    template<typename T, std::size_t... I>
    inline constexpr auto push_impl(const T& val, std::index_sequence<I...>) const {
        return std::make_tuple(std::get<I>(mTuple)... , val);
    };

    tuple_type mTuple;
};

template<typename... Ts>
stack<Ts...> make_stack(const Ts&... args) {
    return stack<Ts...> { args... };
};




template<std::size_t I, std::size_t N, template<std::size_t, std::size_t > class D>
struct base_iterator {
    static constexpr std::size_t size = N, index = I;

    template<std::size_t DerI, std::size_t DerN>
    using derived_type = D<DerI, DerN>;

    inline constexpr operator bool() const {
        return 0 <= index && index < size;
    };
    inline constexpr auto next() const {
        return derived_type<index + 1, size>{};
    };
    inline constexpr auto prev() const {
        return derived_type<index - 1, size>{};
    };
};

template<std::size_t I, std::size_t N>
struct iterator : public base_iterator<I, N, iterator>
{
    typedef base_iterator<I, N, iterator> base_type;
    using base_type::index;

    template<typename... Ts>
    inline constexpr auto& operator() (std::tuple<Ts...>& t) const {
        return std::get<index>(t);
    };
};

template<std::size_t I, std::size_t N>
struct const_iterator : public base_iterator<I, N, const_iterator>
{
    typedef base_iterator<I, N, iterator> base_type;
    using base_type::index;

    template<typename... Ts>
    inline constexpr const auto& operator() (const std::tuple<Ts...>& t) const {
        return std::get<index>(t);
    };
};


};  //-- namespace tuple --
};  //-- namesapce utility --


#endif /* LIB_UTILITY_TUPLE_HPP_ */
