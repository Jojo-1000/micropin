/* PinUtils.hpp
*
* Copyright (C) 2020 Jan Rogall
*
* This software may be modified and distributed under the terms
* of the MIT license.  See the LICENSE file for details.
*/

#ifndef MICROPIN_DETAIL_PINUTILS_INCLUDED
#define MICROPIN_DETAIL_PINUTILS_INCLUDED

#include "detail/PinDefs.hpp"

namespace MicroPin
{
    namespace detail
    {
        template<bool SeparatePullups> // SeparatePullups = false
        class PinModeHelperT
        {
        public:
            inline void pinMode(uint8_t pin, PinType mode)
            {
                pinMode(GetPinDataDirection(num), GetPinData(num), GetRuntimePinBitmask(num), mode);
            }
            template<uint8_t Num>
            __attribute__((always_inline)) inline void pinMode(PinType mode)
            {
                using PortType = Port<detail::GetPinPortN(Num)>;
                pinMode(PortType::GetTypeReg(), PortType::GetPortReg(), PinTraits<Num>::bitmask, mode);
            }

            //Compiler believes this function should not be inlined, but inlining reduces size significantly
            __attribute__((always_inline)) inline void pinMode(Register8 typeReg, Register8 portReg, Bit bitmask, PinType mode)
            {
                NoInterrupts i;
                if (static_cast<uint8_t>(mode) == 0) // input
                {
                    //Set mode to input
                    typeReg.Clear(bitmask);
                    portReg.Clear(bitmask);
                    pullupReg.Clear(bitmask);
                }
                else if(static_cast<uint8_t>(mode) == 1) //output
                {
                    //Set mode to output
                    typeReg.Set(bitmask);
                    pullupReg.Clear(bitmask);
                }
                else // input pullup
                {
                    typeReg.Clear(bitmask);
                    portReg.Set(bitmask);
                    pullupReg.Set(bitmask);
                }
            }
        };

        template<>
        class PinModeHelperT<true> // SeparatePullups = true
        {
        public:
            inline void pinMode(uint8_t pin, PinType mode)
            {
                pinMode(GetPinDataDirection(num), GetPinData(num), GetRuntimePinBitmask(num), mode);
            }
            template<uint8_t Num>
            __attribute__((always_inline)) inline void pinMode(PinType mode)
            {
                pinMode(GetPinDataDirection(Num), GetPinData(Num), GetPinPullupEnable(Num), PinTraits<Num>::bitmask, mode);
            }

            //Compiler believes this function should not be inlined, but inlining reduces size significantly
            __attribute__((always_inline)) inline void pinMode(Register8 typeReg, Register8 portReg, Register8 pullupReg, Bit bitmask, PinType mode)
            {
                NoInterrupts i;
                if(mode == PinMode::input)
                if ((static_cast<uint8_t>(mode) & 0x01) == 0)
                {
                    //Set mode to input
                    typeReg &= ~bitmask;
                }
                else
                {
                    //Set mode to output
                    typeReg |= bitmask;
                }
                // Write
                portReg |= bitmask;
                if ((static_cast<uint8_t>(mode) & 0x02) == 0)
                {
                    //Write low/disable pullup
                    portReg &= ~bitmask;
                    pullupReg &= ~bitmask;
                }
                else
                {
                    //Write high/enable pullup
                    
                    pullupReg |= bitmask;
                }
            }
        };

        using PinModeHelper = PinModeHelperT<hasSeparatePullups>;

        //analogPin = analog pin number (0-7), not actual pin number
        inline uint16_t analogRead(uint8_t analogPin)
        {
            rADMUX = (rADMUX & 0xF0) | (analogPin & 0x0F);
            //Start conversion
            rADCSRA = (bADEN | bADSC) | MicroPin::detail::prescaleADC;
            //Wait
            while (rADCSRA & bADSC);
            return rADCW;
        }

        template<bool Cli = true>
        class PinWrite {};
        template<>
        class PinWrite<false>
        {
        public:
            __attribute__((always_inline)) static void digitalWrite(Register8 portReg, Bit bitmask, bool on)
            {
                if (on)
                {
                    digitalWriteOn(portReg, bitmask);
                }
                else
                {
                    digitalWriteOff(portReg, bitmask);
                }
            }
            __attribute__((always_inline)) static void digitalWriteOn(Register8 portReg, Bit bitmask)
            {
                portReg |= bitmask;
            }
            __attribute__((always_inline)) static void digitalWriteOff(Register8 portReg, Bit bitmask)
            {
                portReg &= ~bitmask;
            }
        };
        template<>
        class PinWrite<true>
        {
        public:
            __attribute__((always_inline)) static void digitalWrite(Register8 portReg, Bit bitmask, bool on)
            {
                NoInterrupts ni;
                if (on)
                {
                    PinWrite<false>::digitalWriteOn(portReg, bitmask);
                }
                else
                {
                    PinWrite<false>::digitalWriteOff(portReg, bitmask);
                }
            }
            __attribute__((always_inline)) static void digitalWriteOn(Register8 portReg, Bit bitmask)
            {
                NoInterrupts ni;
                portReg |= bitmask;
            }
            __attribute__((always_inline)) static void digitalWriteOff(Register8 portReg, Bit bitmask)
            {
                NoInterrupts ni;
                portReg &= ~bitmask;
            }
        };
    }
}

#endif
