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
	struct PinBitmaskTag{};
	struct PinTimerTag{};
	using PinBitmask = ConstexprProgmemArray<PinBitmaskTag, uint8_t, 22,
		0x01,	// pin  0
		0x02,	// pin  1
		0x04,	// pin  2
		0x08,	// pin  3
		0x10,	// pin  4
		0x20,	// pin  5
		0x40,	// pin  6
		0x80,	// pin  7
		
		0x01,	// pin  8
		0x02,	// pin  9
		0x04,	// pin 10
		0x08,	// pin 11
		0x10,	// pin 12
		0x20,	// pin 13
		
		0x01,	// pin A0
		0x02,	// pin A1
		0x04,	// pin A2
		0x08,	// pin A3
		0x10,	// pin A4
		0x20,	// pin A5
		0x40,	// pin A6
		0x80	// pin A7
		>;
	using PinTimer = ConstexprProgmemArray<PinTimerTag, uint8_t, 22,
		0, /* 0 - port D */
		0,
		0,
		6,	// TIMER2B
		0,
		2,	// TIMER0B
		1,	// TIMER0A
		0,
		0, /* 8 - port B */
		3,	// TIMER1A
		4,	// TIMER1B
		5,	// TIMER2A
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

inline uint8_t MicroPin::detail::GetRuntimePinBitmask(uint8_t pin)
{
	return PinBitmask::RuntimeRead(pin);
}
inline uint8_t MicroPin::detail::GetRuntimePinTimer(uint8_t pin)
{
	return PinTimer::RuntimeRead(pin);
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
	return port == 0 ? rPIND : (port == 1 ? rPINB :	rPINC);
}
constexpr MicroPin::Register8 MicroPin::detail::GetPinDataDirection(uint8_t pin)
{
	return GetPortDataDirection(GetPinPortN(pin));
}
constexpr MicroPin::Register8 MicroPin::detail::GetPinData(uint8_t pin)
{
	return GetPortData(GetPinPortN(pin));
}
constexpr MicroPin::Register8 MicroPin::detail::GetPinInput(uint8_t pin)
{
	return GetPortInput(GetPinPortN(pin));
}

//Does not check input range
constexpr uint8_t MicroPin::detail::GetAnalogPort(uint8_t digitalPin)
{
	return digitalPin - 14;
}

namespace MicroPin
{
namespace detail
{
	template<uint8_t Num, bool Analog = false, bool Digital = true>
	struct PinTraitsHelper
	{
		static constexpr bool exists = true;
		static constexpr bool hasTimer = PinTimer::Get<Num>() != 0;
		static constexpr bool isAnalog = Analog;
		static constexpr bool hasDigital = Digital;
		static constexpr uint8_t bitmask = PinBitmask::Get<Num>();
		static constexpr uint8_t timer = PinTimer::Get<Num>();
	};
	//Port D
	template<> struct PinTraits<0> : PinTraitsHelper<0>{};
	template<> struct PinTraits<1> : PinTraitsHelper<1>{};
	template<> struct PinTraits<2> : PinTraitsHelper<2>{};
	template<> struct PinTraits<3> : PinTraitsHelper<3>{};
	template<> struct PinTraits<4> : PinTraitsHelper<4>{};
	template<> struct PinTraits<5> : PinTraitsHelper<5>{};
	template<> struct PinTraits<6> : PinTraitsHelper<6>{};
	template<> struct PinTraits<7> : PinTraitsHelper<7>{};
	//Port B
	template<> struct PinTraits<8> : PinTraitsHelper<8>{};
	template<> struct PinTraits<9> : PinTraitsHelper<9>{};
	template<> struct PinTraits<10> : PinTraitsHelper<10>{};
	template<> struct PinTraits<11> : PinTraitsHelper<11>{};
	template<> struct PinTraits<12> : PinTraitsHelper<12>{};
	template<> struct PinTraits<13> : PinTraitsHelper<13>{};
	//Port C
	template<> struct PinTraits<14> : PinTraitsHelper<14, true>{};
	template<> struct PinTraits<15> : PinTraitsHelper<15, true>{};
	template<> struct PinTraits<16> : PinTraitsHelper<16, true>{};
	template<> struct PinTraits<17> : PinTraitsHelper<17, true>{};
	template<> struct PinTraits<18> : PinTraitsHelper<18, true>{};
	template<> struct PinTraits<19> : PinTraitsHelper<19, true>{};
	template<> struct PinTraits<20> : PinTraitsHelper<20, true, false>{};
	template<> struct PinTraits<21> : PinTraitsHelper<21, true, false>{};
}
}


#endif