/* detail/pin-defs/ATtiny441.h
 *
 * Copyright (C) 2018 Jan Rogall
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */


#ifndef MICROPIN_DETAIL_PINDEFS_ATTINYX41_INCLUDED
#define MICROPIN_DETAIL_PINDEFS_ATTINYX41_INCLUDED

#include "../../ConstexprProgmem.hpp"

 // Pinout based on https://github.com/SpenceKonde/ATTinyCore/blob/master/avr/extras/ATtiny_x41.md (clockwise)

namespace MicroPin
{
    namespace detail
    {
        struct PinBitmaskTag {};
        struct PinTimerTag {};
        using PinBitmask = ConstexprProgmemArray<PinBitmaskTag, Bit,
            0_bit, // pin 0
            1_bit, // pin 1
            2_bit, // pin 2
            3_bit, // pin 3
            4_bit, // pin 4
            5_bit, // pin 5
            6_bit, // pin 6
            7_bit, // pin 7

            2_bit, // pin 8
            1_bit, // pin 9
            0_bit, // pin 10
            3_bit // pin 11
        >;
        using PinTimer = ConstexprProgmemArray<PinTimerTag, uint8_t,
            0, // pin 0
            0, // pin 1
            0, // pin 2
            4, // pin 3: OC1B
            1, // pin 4: OC0A
            2, // pin 5: OC0B
            3, // pin 6: OC1A
            6, // pin 7: OC2B

            5, // pin 8: OC2A
            0, // pin 9
            0, // pin 10
            0 // pin 11
        >;
    }
}

inline MicroPin::Bit MicroPin::detail::GetRuntimePinBitmask(uint8_t pin)
{
    return PinBitmask::RuntimeRead(pin);
}
inline uint8_t MicroPin::detail::GetRuntimePinTimer(uint8_t pin)
{
    return PinTimer::RuntimeRead(pin);
}
constexpr uint8_t MicroPin::detail::GetPinPortN(uint8_t pin)
{
    // Port A: 0-7
    // Port B: 8-11
    return pin > 7 ? 1 : 0;
}
constexpr MicroPin::Register8 MicroPin::detail::GetPortDataDirection(uint8_t port)
{
    return  port ? rDDRA : rDDRB;
}
constexpr MicroPin::Register8 MicroPin::detail::GetPortData(uint8_t port)
{
    return port ? rPORTA : rPORTB;
}
constexpr MicroPin::Register8 MicroPin::detail::GetPortInput(uint8_t port)
{
    return port ? rPINA : rPINB;
}

inline void MicroPin::detail::ClearPWM(uint8_t timer)
{
    switch (timer)
    {
    case 1:
        rTCCR0A.Clear(bCOM0A1);
        break;
    case 2:
        rTCCR0A.Clear(bCOM0B1);
        break;
    case 3:
        rTCCR1A.Clear(bCOM1A1);
        break;
    case 4:
        rTCCR1A.Clear(bCOM1B1);
        break;
    case 5:
        rTCCR2A.Clear(bCOM2A1);
        break;
    case 6:
        rTCCR2A.Clear(bCOM2B1);
        break;
    }
}
inline void MicroPin::detail::AnalogWrite(uint8_t timerNum, uint8_t value)
{
    switch (timerNum)
    {
    case 1:
        rTCCR0A.Set(bCOM0A1);
        rOCR0A = value;
        break;
    case 2:
        rTCCR0A.Set(bCOM0B1);
        rOCR0B = value;
        break;
    case 3:
        rTCCR1A.Set(bCOM1A1);
        rOCR1A = value;
        break;
    case 4:
        rTCCR1A.Set(bCOM1B1);
        rOCR1B = value;
        break;
    case 5:
        rTCCR2A.Set(bCOM2A1);
        rOCR2A = value;
        break;
    case 6:
        rTCCR2A.Set(bCOM2B1);
        rOCR2B = value;
        break;
    }
}
//Does not check input range
constexpr uint8_t MicroPin::detail::GetAnalogChannel(uint8_t digitalPin)
{
    // Pins 0-8 correspond with their analog channel
    // Pin 9: ADC10
    // Pin 10: ADC11
    // Pin 11: ADC9
    return digitalPin < 9 ? digitalPin : (digitalPin == 11 ? 9 : (digitalPin == 9 ? 10 : 11));
}

// There are so few pins that the array size does not matter
inline uint8_t MicroPin::detail::GetRuntimePinTimer(uint8_t pin)
{
    return PinTimer::RuntimeRead(pin);
}

constexpr bool MicroPin::detail::IsAnalogPin(uint8_t num)
{
    return true;
}

constexpr bool MicroPin::detail::IsDigitalPin(uint8_t num)
{
    return true;
}

#endif