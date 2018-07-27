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
    template<typename T>
    struct PgmReadSelect {};
    template<> struct PgmReadSelect<uint8_t>
    {
        static uint8_t Read(const uint8_t* addr)
        {
            return pgm_read_byte(addr);
        }
    };
    template<> struct PgmReadSelect<uint16_t>
    {
        static uint16_t Read(const uint16_t* addr)
        {
            return pgm_read_word(addr);
        }
    };
    template<> struct PgmReadSelect<uint32_t>
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
    template<typename Tag, typename T, size_t Num, T... Values>
    class ConstexprProgmemArray
    {
    public:
        //Only used as static typedef
        ConstexprProgmemArray() = delete;

        using InternalType = T[Num];
        static_assert(Num == sizeof...(Values), "Wrong number of values given");
        static_assert(is_same<decltype(detail::PgmReadSelect<T>::Read), T(const T*)>::value, "Unsupported data type");

        static const T data[Num] PROGMEM;
        static T RuntimeRead(size_t index)
        {
            return detail::PgmReadSelect<T>::Read(data + index * sizeof(T));
        }
        template<size_t I>
        static constexpr T Get()
        {
            return get<I>(make_own_tuple(Values...));
        }
    };
}

//Definition
template<typename Tag, typename T, size_t Num, T... Values>
const T MicroPin::ConstexprProgmemArray<Tag, T, Num, Values...>::data[Num] PROGMEM = {Values...};

#endif
