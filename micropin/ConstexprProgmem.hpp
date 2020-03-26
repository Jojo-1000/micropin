/* ConstxprProgmem.h
 *
 * Copyright (C) 2018 Jan Rogall
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */


#ifndef MICROPIN_CONSTEXPR_PROGMEM_INCLUDED
#define MICROPIN_CONSTEXPR_PROGMEM_INCLUDED

#include "ModernSTL.hpp"
#include "TypeTraits.hpp"
#include <avr/pgmspace.h>

namespace MicroPin
{
namespace detail
{
    template<typename T, typename Enable = void>
    struct PgmReadSelect {};
    template<typename T>
    struct PgmReadSelect<T, enable_if_t<(is_integral<T>::value || is_enum<T>::value ) && sizeof(T) == 1>>
    {
        static T Read(const T* addr)
        {
            return static_cast<T>(pgm_read_byte(addr));
        }
    };
    template<typename T> 
    struct PgmReadSelect<T, enable_if_t<(is_integral<T>::value || is_enum<T>::value) && sizeof(T) == 2>>
    {
        static T Read(const T* addr)
        {
            return static_cast<T>(pgm_read_word(addr));
        }
    };
    template<typename T>
    struct PgmReadSelect<T, enable_if_t<(is_integral<T>::value || is_enum<T>::value) && sizeof(T) == 4>>
    {
        static uint32_t Read(const uint32_t* addr)
        {
            return pgm_read_dword(addr);
        }
    };
    template<> struct PgmReadSelect<float>
    {
        static float Read(const float* addr)
        {
            return pgm_read_float(addr);
        }
    };
    
}


    //Saves array of values for both compile time and runtime access
    //Usage:
    //  struct XXXTag{};
    //  using XXX = ConstexprProgmemArray<XXXTag, T, N, values...>;
    //  ...
    //  a = XXX::RuntimeRead(i);
    //  b = XXX::Get<I>();
    //Tag: uniquely identify static data
    template<typename Tag, typename T, T... Values>
    class ConstexprProgmemArray
    {
    public:
        //Only used as static typedef
        ConstexprProgmemArray() = delete;

        using InternalType = T[sizeof...(Values)];
        //static_assert(Num == sizeof...(Values), "Wrong number of values given");
        static_assert(is_same<decltype(detail::PgmReadSelect<T>::Read), T(const T*)>::value, "Unsupported data type");

        static const T data[sizeof...(Values)] PROGMEM;
        static T RuntimeRead(size_t index)
        {
            return detail::PgmReadSelect<T>::Read(data + index);
        }
        template<size_t I>
        static constexpr T Get()
        {
            static_assert(I < sizeof...(Values), "Get index too high");
            return get<I>(make_own_tuple(Values...));
        }
    };
}

//Definition
template<typename Tag, typename T, T... Values>
const T MicroPin::ConstexprProgmemArray<Tag, T, Values...>::data[sizeof...(Values)] PROGMEM = {Values...};

#endif
