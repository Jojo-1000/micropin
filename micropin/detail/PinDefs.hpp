/* detail/PinDefs.h
 *
 * Copyright (C) 2018 Jan Rogall
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */


#ifndef MICROPIN_DETAIL_PINDEFS_INCLUDED
#define MICROPIN_DETAIL_PINDEFS_INCLUDED

#include "../Register.hpp"

namespace MicroPin
{
namespace detail
{
    // Processor specific
    constexpr Register8 GetPortDataDirection(uint8_t port);
    constexpr Register8 GetPortData(uint8_t port);
    constexpr Register8 GetPortInput(uint8_t port);

    inline void ClearPWM(uint8_t timer);
    inline void AnalogWrite(uint8_t timer, uint8_t value);

    // Pinout specific (Board specific)
    inline Bit GetRuntimePinBitmask(uint8_t pin);
    inline uint8_t GetRuntimePinTimer(uint8_t pin);
    constexpr uint8_t GetPinPortN(uint8_t pin);
    
    constexpr Register8 GetPinDataDirection(uint8_t pin)
    {
        return GetPortDataDirection(GetPinPortN(pin));
    }
    constexpr Register8 GetPinData(uint8_t pin)
    {
        return GetPortData(GetPinPortN(pin));
    }
    constexpr Register8 GetPinInput(uint8_t pin)
    {
        return GetPortInput(GetPinPortN(pin));
    }

    
    constexpr bool IsAnalogPin(uint8_t num);
    constexpr bool IsDigitalPin(uint8_t num);
    //Does not check input range
    constexpr uint8_t GetAnalogChannel(uint8_t digitalPin);

    template<uint8_t Num, typename Enable = void>
    struct PinTraits
    {
        static constexpr bool exists = false;
        //static constexpr bool hasTimer;
        //static constexpr bool isAnalog;
        //static constexpr bool hasDigital;
        //static constexpr Bit bitmask;
        //static constexpr uint8_t timer;
    };

    constexpr bool hasSeparatePullups;
}
}

//Different definitions
#if defined(__AVR_ATmega48A__) || defined(__AVR_ATmega48PA__) \
    || defined(__AVR_ATmega88A__) || defined(__AVR_ATmega88PA__) \
    || defined(__AVR_ATmega168A__) || defined(__AVR_ATmega168PA__) \
    || defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__)
#   include "pin-defs/ATmegaX8.hpp"
#elif defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
#   include "pin-defs/ATtinyX5.hpp"
#elif defined(__AVR_ATtiny441__) || defined(__AVR_ATtiny841)
#   include "pin-defs/ATtinyX41.hpp"
#else
#   error "Unsupported device"
#endif

namespace MicroPin
{
namespace detail
{
    template<uint8_t Num>
    struct PinTraits<Num, enable_if_t<(Num < PinBitmask::Size())>>
    {
        static constexpr bool exists = true;
        static constexpr bool hasTimer = PinTimer::Get<Num>() != 0;
        static constexpr bool isAnalog = IsAnalogPin(Num);
        static constexpr bool hasDigital = IsDigitalPin(Num);
        static constexpr Bit bitmask = PinBitmask::Get<Num>();
        static constexpr uint8_t timer = PinTimer::Get<Num>();
    };
}
}

inline MicroPin::Bit MicroPin::detail::GetRuntimePinBitmask(uint8_t pin)
{
    return PinBitmask::RuntimeRead(pin);
}

#endif
