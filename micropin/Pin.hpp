/* Pin.h
 *
 * Copyright (C) 2018 Jan Rogall
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */


#ifndef MICROPIN_PIN_INCLUDED
#define MICROPIN_PIN_INCLUDED

#include <stdint.h>
#include "RegisterDefinitions.hpp"

#include "Register.hpp"
#include "Interrupts.hpp"
#include "detail/ADC.hpp"
#include "detail/PinDefs.hpp"

namespace MicroPin
{
    //Types for high and low, for compile time optimization if available
    struct HighType
    {
        constexpr operator bool() const
        {
            return true;
        }
    };
    struct LowType
    {
        constexpr operator bool() const
        {
            return false;
        }
    };
    //HIGH is convertible to true, but use it instead for more optimizations
    constexpr HighType high;
    //LOW is convertible to false, but use it instead for more optimizations
    constexpr LowType low;

    struct PinType
    {
        constexpr PinType(uint8_t value) : value(value){}
        uint8_t value = 0;
        constexpr explicit operator uint8_t() const
        {
            return value;
        }
    };
    struct PinTypeInput
    {
        constexpr PinTypeInput() = default;
        constexpr operator PinType() const
        {
            return PinType{0};
        }
    };
    struct PinTypeOutput
    {
        constexpr PinTypeOutput() = default;
        constexpr operator PinType() const
        {
            return PinType{1};
        }
    };
    struct PinTypeInputPullup
    {
        constexpr PinTypeInputPullup() = default;
        constexpr operator PinType() const
        {
            return PinType{2};
        }
    };

    constexpr PinTypeInput input;
    constexpr PinTypeOutput output;
    constexpr PinTypeInputPullup inputPullup;

    template<uint8_t Num>
    class Port
    {
    public:
        static constexpr Register8 GetTypeReg()
        {
            return detail::GetPortDataDirection(Num);
        }
        static constexpr Register8 GetPortReg()
        {
            return detail::GetPortData(Num);
        }
        static constexpr Register8 GetDataReg()
        {
            return detail::GetPortInput(Num);
        }
    };

    namespace Utils
    {
        //Compiler believes this function should not be inlined, but inlining reduces size significantly
        __attribute__((always_inline)) inline void pinMode(Register8 typeReg, Register8 portReg, Bit bitmask, PinType mode)
        {
            NoInterrupts i;
            if((static_cast<uint8_t>(mode) & 0x01) == 0)
            {
                //Set mode to input
                typeReg &= ~bitmask;
            }
            else
            {
                //Set mode to output
                typeReg |= bitmask;
            }
            if((static_cast<uint8_t>(mode) & 0x02) == 0)
            {
                //Write low/disable pullup
                portReg &= ~bitmask;
            }
            else
            {
                //Write high/enable pullup
                portReg |= bitmask;
            }
        }
        namespace detail
        {
            __attribute__((always_inline)) inline void internalDigitalWriteOn(Register8 portReg, Bit bitmask)
            {
                portReg |= bitmask;
            }
            __attribute__((always_inline)) inline void internalDigitalWriteOff(Register8 portReg, Bit bitmask)
            {
                portReg &= ~bitmask;
            }
        }
        __attribute__((always_inline)) inline void digitalWrite(Register8 portReg, Bit bitmask, bool on)
        {
            //detail::internalDigitalWriteOn/Off can be used directly if portReg, bitmask and on are all known at compile time
            NoInterrupts i;
            if(on)
            {
                detail::internalDigitalWriteOn(portReg, bitmask);
            }
            else
            {
                detail::internalDigitalWriteOff(portReg, bitmask);
            }
        }
        __attribute__((always_inline)) inline bool digitalRead(Register8 dataReg, Bit bitmask)
        {
            return dataReg & bitmask;
        }
        //analogPin = analog pin number (0-7), not actual pin number
        inline uint16_t analogRead(uint8_t analogPin)
        {
            rADMUX = (rADMUX & 0xF0) | (analogPin & 0x0F);
            //Start conversion
            rADCSRA = (bADEN | bADSC) | MicroPin::detail::prescaleADC;
            //Wait
            while(rADCSRA & bADSC);
            return rADCW;
        }
    }

    template<uint8_t Num>
    class StaticDigitalPin
    {
    private:
        using PinTraits = detail::PinTraits<Num>;
    public:
        constexpr StaticDigitalPin() = default;
        static_assert(detail::PinTraits<Num>::exists, "Pin number does not exist");
        using PortType = Port<detail::GetPinPortN(Num)>;
        void pinMode(PinType mode) const
        {
            Utils::pinMode(PortType::GetTypeReg(), PortType::GetPortReg(), PinTraits::bitmask, mode);
        }
        void operator=(bool on) const
        {
            static_assert(PinTraits::hasDigital, "Cannot digital write on pin without digital buffers");
            Utils::digitalWrite(PortType::GetPortReg(), PinTraits::bitmask, on);
        }
        __attribute__((always_inline)) void operator=(HighType) const
        {
            static_assert(PinTraits::hasDigital, "Cannot digital write on pin without digital buffers");
            //Directly turn on, without disabling interrupts as all values are constexpr
            Utils::detail::internalDigitalWriteOn(PortType::GetPortReg(), PinTraits::bitmask);
        }
        __attribute__((always_inline)) void operator=(LowType) const
        {
            static_assert(PinTraits::hasDigital, "Cannot digital write on pin without digital buffers");
            //Directly turn off, without disabling interrupts as all values are constexpr
            Utils::detail::internalDigitalWriteOff(PortType::GetPortReg(), PinTraits::bitmask);
        }
        operator bool() const
        {
            static_assert(PinTraits::hasDigital, "Cannot digital read on pin without digital buffers");
            return Utils::digitalRead(PortType::GetDataReg(), PinTraits::bitmask);
        }
    };
    template<uint8_t Num>
    class StaticPWMPin : public StaticDigitalPin<Num>
    {
    private:
        using PinTraits = detail::PinTraits<Num>;
        using Base = StaticDigitalPin<Num>;
    public:
        static_assert(PinTraits::hasTimer, "Pin does not have timer, cannot use StaticPWMPin");
        void operator=(bool on) const
        {
            clearPWM();
            Base::operator =(on);
        }
        void operator=(HighType) const
        {
            clearPWM();
            Base::operator =(HighType{});
        }
        void operator=(LowType) const
        {
            clearPWM();
            Base::operator =(LowType{});
        }
        operator bool() const
        {
            clearPWM();
            return Base::operator bool();
        }
        void analogWrite(uint8_t val) const
        {
            if(val == 0)
            {
                *this = 0;
            }
            else if(val == 255)
            {
                *this = 255;
            }
            else
            {
                detail::AnalogWrite(PinTraits::timer, val);
            }
        }
        void clearPWM() const
        {
            detail::ClearPWM(PinTraits::timer);
        }
    };
    template<uint8_t Num>
    class StaticAnalogPin
    {
    private:
        using PinTraits = detail::PinTraits<Num>;
    public:
        static_assert(PinTraits::exists, "Pin number does not exist");
        static_assert(PinTraits::isAnalog, "Pin is not an analog input, cannot use StaticAnalogPin");
        constexpr StaticAnalogPin() = default;
        uint16_t analogRead() const
        {
            return Utils::analogRead(detail::GetAnalogPort(Num));
        }
    };
    template<uint8_t Num>
    class StaticAnalogDigitalPin : public StaticDigitalPin<Num>, public StaticAnalogPin<Num>
    {};
    //There is no analog input pin with PWM

    class DigitalPin
    {
    public:
        explicit DigitalPin(uint8_t num)
            :num(num)
        {}
        void pinMode(PinType mode) const
        {
            Utils::pinMode(detail::GetPinDataDirection(num), detail::GetPinData(num), detail::GetRuntimePinBitmask(num), mode);
        }
        void operator=(bool on) const
        {
            Utils::digitalWrite(detail::GetPinData(num), detail::GetRuntimePinBitmask(num), on);
        }
        operator bool() const
        {
            return Utils::digitalRead(detail::GetPinInput(num), detail::GetRuntimePinBitmask(num));
        }
        uint8_t GetNum() const
        {
            return num;
        }
    private:
        uint8_t num;
    };

    class PWMPin : public DigitalPin
    {
    public:
        explicit PWMPin(uint8_t num)
            : DigitalPin(num)
        {}
        void operator=(bool on) const
        {
            clearPWM();
            DigitalPin::operator =(on);
        }
        operator bool() const
        {
            clearPWM();
            return DigitalPin::operator bool();
        }
        void analogWrite(uint8_t val) const
        {
            if(val == 0)
            {
                *this = 0;
            }
            else if(val == 255)
            {
                *this = 255;
            }
            else
            {
                const uint8_t timerNum = detail::GetRuntimePinTimer(GetNum());
                if(timerNum != 0)
                {
                    detail::AnalogWrite(timerNum, val);
                }
                else
                {
                    //Set to closer value
                    DigitalPin::operator =(val >= 128);
                }
            }
        }
        void clearPWM() const
        {
            uint8_t timerNum = detail::GetRuntimePinTimer(GetNum());
            if(timerNum != 0)
            {
                detail::ClearPWM(timerNum);
            }
        }
    };
    class AnalogPin
    {
    public:
        //analogPinNum (0-7) != pinNum!!!
        explicit AnalogPin(uint8_t analogPinNum)
            :analogPinNum(analogPinNum)
        {}
        uint16_t analogRead() const
        {
            return Utils::analogRead(analogPinNum);
        }
    private:
        uint8_t analogPinNum;
    };
    class AnalogDigitalPin : public DigitalPin
    {
    //Reimplemented AnalogPin's functionality, because otherwise there would be 1 byte overhead
    public:
        explicit AnalogDigitalPin(uint8_t num)
            :DigitalPin(num)
        {}
        uint16_t analogRead() const
        {
            return Utils::analogRead(detail::GetAnalogPort(GetNum()));
        }
    };
}

#endif
