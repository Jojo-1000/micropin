/* Register.h
 *
 * Copyright (C) 2018 Jan Rogall
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */


#ifndef MICROPIN_REGISTER_INCLUDED
#define MICROPIN_REGISTER_INCLUDED

#include <stdint.h>

#include "TypeTraits.hpp"

namespace MicroPin
{
    enum class Bit : uint8_t
    {};

    //Literal to create bit enums
    constexpr Bit operator""_bit(unsigned long long i)
    {
        return static_cast<Bit>(i);
    }
    constexpr uint8_t operator|(Bit l, Bit r)
    {
        return (1 << static_cast<uint8_t>(l)) | (1 << static_cast<uint8_t>(r));
    }
    constexpr uint8_t operator~(Bit b)
    {
        return ~(1 << static_cast<uint8_t>(b));
    }
    constexpr uint8_t operator&(uint8_t l, Bit r)
    {
        return l & (1 << static_cast<uint8_t>(r));
    }
    constexpr uint8_t operator&(Bit l, uint8_t r)
    {
        return r & l;
    }
    constexpr uint8_t operator|(uint8_t l, Bit r)
    {
        return l | (1 << static_cast<uint8_t>(r));
    }
    constexpr uint8_t operator|(Bit l, uint8_t r)
    {
        return r | l;
    }

    template<typename T>
    class Register
    {
        uint8_t addr;
        static_assert(is_integral<T>::value, "Register must contain integral type");
        public:
        explicit constexpr Register(uint8_t i) : addr(i)
        {}
        operator volatile T&() const
        {
            return *reinterpret_cast<volatile T*>(addr);
        }
        constexpr uint8_t GetIntAddr() const
        {
            return addr;
        }
        volatile T* GetAddr() const
        {
            return *reinterpret_cast<volatile T*>(addr);
        }
        const Register& operator=(const T& value) const
        {
            *reinterpret_cast<volatile T*>(addr) = value;
            return *this;
        }
        template<typename V, enable_if_t<is_integral<V>::value>* = nullptr>
        friend Register<T> operator|=(Register<T> r, V value)
        {
            *reinterpret_cast<volatile T*>(r.addr) |= value;
            return r;
        }
        template<typename V, enable_if_t<is_integral<V>::value>* = nullptr>
        friend Register operator&=(Register r, V value)
        {
            *reinterpret_cast<volatile T*>(r.addr) &= value;
            return r;
        }

        friend Register operator|=(Register r, Bit bit)
        {
            *reinterpret_cast<volatile T*>(r.addr) |= (1 << static_cast<uint8_t>(bit));
            return r;
        }
        friend Register operator&=(Register r, Bit bit)
        {
            *reinterpret_cast<volatile T*>(r.addr) &= (1 << static_cast<uint8_t>(bit));
            return r;
        }
    };

    using Register8 = Register<uint8_t>;
    using Register16 = Register<uint16_t>;
    static_assert(sizeof(Register8) == 1, "Register size might indicate performance losses");
}

#endif
