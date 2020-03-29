/* detail/pin-defs/ATmegaX8.h
*
* Copyright (C) 2018 Jan Rogall
*
* This software may be modified and distributed under the terms
* of the MIT license.  See the LICENSE file for details.
*/


#ifndef MICROPIN_DETAIL_PINDEFS_ATMEGAX8_INCLUDED
#define MICROPIN_DETAIL_PINDEFS_ATMEGAX8_INCLUDED

#include "../../ConstexprProgmem.hpp"

namespace MicroPin
{
    namespace detail
    {
        using PinBitmask = ConstexprProgmemArray<Bit,
        0_bit,    // pin  0
        1_bit,    // pin  1
        2_bit,    // pin  2
        3_bit,    // pin  3
        4_bit,    // pin  4
        5_bit,    // pin  5
        6_bit,    // pin  6
        7_bit,    // pin  7

        0_bit,    // pin  8
        1_bit,    // pin  9
        2_bit,    // pin 10
        3_bit,    // pin 11
        4_bit,    // pin 12
        5_bit,    // pin 13

        0_bit,    // pin A0
        1_bit,    // pin A1
        2_bit,    // pin A2
        3_bit,    // pin A3
        4_bit,    // pin A4
        5_bit,    // pin A5
        6_bit,    // pin A6
        7_bit     // pin A7 (does not actually have a register value)
        >;
        using PinTimer = ConstexprProgmemArray<uint8_t,
        0, /* 0 - port D */
        0,
        0,
        6,    // TIMER2B
        0,
        2,    // TIMER0B
        1,    // TIMER0A
        0,
        0, /* 8 - port B */
        3,    // TIMER1A
        4,    // TIMER1B
        5,    // TIMER2A
        0,
        0,
        0,
        0, /* 14 - port C */
        0,
        0,
        0,
        0,
        0,
        0>;
    }
}

constexpr uint8_t MicroPin::detail::GetPinPortN(uint8_t pin)
{
    // pin  0 - 7 -> port 0
    // pin  8 - 13 -> port 1
    // pin A0 - A7 (14 - 21) -> port 2
    return pin < 8 ? 0 : (pin < 14 ? 1 : 2);
}
constexpr MicroPin::Register8 MicroPin::detail::GetPortDataDirection(uint8_t port)
{
    return port == 0 ? rDDRD : (port == 1 ? rDDRB : rDDRC);
}
constexpr MicroPin::Register8 MicroPin::detail::GetPortData(uint8_t port)
{
    return port == 0 ? rPORTD : (port == 1 ? rPORTB : rPORTC);
}
constexpr MicroPin::Register8 MicroPin::detail::GetPortInput(uint8_t port)
{
    return port == 0 ? rPIND : (port == 1 ? rPINB :    rPINC);
}

inline void MicroPin::detail::ClearPWM(uint8_t timer)
{
    switch(timer)
    {
        case 1:
        rTCCR0A &= ~bCOM0A1;
        break;
        case 2:
        rTCCR0A &= ~bCOM0B1;
        break;
        case 3:
        rTCCR1A &= ~bCOM1A1;
        break;
        case 4:
        rTCCR1A &= ~bCOM1B1;
        break;
        case 5:
        rTCCR2A &= ~bCOM2A1;
        break;
        case 6:
        rTCCR2A &= ~bCOM2B1;
        break;
    }
}

inline void MicroPin::detail::AnalogWrite(uint8_t timerNum, uint8_t value)
{
    //6    {&TCCR2A, &OCR2B, COM2B1},    // pin  3
    //2    {&TCCR0A, &OCR0B, COM0B1},    // pin  5
    //1    {&TCCR0A, &OCR0A, COM0A1},    // pin  6
    //3    {&TCCR1A, &OCR1A, COM1A1},    // pin  9
    //4    {&TCCR1A, &OCR1B, COM1B1},    // pin 10
    //5    {&TCCR2A, &OCR2A, COM2A1},    // pin 11
    switch(timerNum)
    {
        case 1:
        rTCCR0A |= bCOM0A1;
        rOCR0A = value;
        break;
        case 2:
        rTCCR0A |= bCOM0B1;
        rOCR0B = value;
        break;
        case 3:
        rTCCR1A |= bCOM1A1;
        rOCR1A = value;
        break;
        case 4:
        rTCCR1A |= bCOM1B1;
        rOCR1B = value;
        break;
        case 5:
        rTCCR2A |= bCOM2A1;
        rOCR2A = value;
        break;
        case 6:
        rTCCR2A |= bCOM2B1;
        rOCR2B = value;
        break;
    }
}

constexpr bool MicroPin::detail::IsAnalogPin(uint8_t num)
{
    return num > 14 && num < PinBitmask::Size();
}

constexpr bool MicroPin::detail::IsDigitalPin(uint8_t num)
{
    return num < 20;
}

//Does not check input range
constexpr uint8_t MicroPin::detail::GetAnalogChannel(uint8_t digitalPin)
{
    return digitalPin - 14;
}

// Switch statement uses less memory than saving the entire array in this case
inline uint8_t MicroPin::detail::GetRuntimePinTimer(uint8_t pin)
{
    //return PinTimer::RuntimeRead(pin);
    switch(pin) {
        case 3: return 6;
        case 5: return 2;
        case 6: return 1;
        case 9: return 3;
        case 10: return 4;
        case 11: return 5;
        default: return 0;
    }
}

#endif
