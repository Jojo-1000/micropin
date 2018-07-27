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
	inline uint8_t GetRuntimePinBitmask(uint8_t pin);
	inline uint8_t GetRuntimePinTimer(uint8_t pin);
	constexpr uint8_t GetPinPortN(uint8_t pin);
	constexpr Register8 GetPortDataDirection(uint8_t port);
	constexpr Register8 GetPortData(uint8_t port);
	constexpr Register8 GetPortInput(uint8_t port);
	constexpr Register8 GetPinDataDirection(uint8_t pin);
	constexpr Register8 GetPinData(uint8_t pin);
	constexpr Register8 GetPinInput(uint8_t pin);

	inline void ClearPWM(uint8_t timer);
	inline void AnalogWrite(uint8_t timer, uint8_t value);

	//Does not check input range
	constexpr uint8_t GetAnalogPort(uint8_t digitalPin);
		
	template<uint8_t Num>
	struct PinTraits
	{
		static constexpr bool exists = false;
		//static constexpr bool hasTimer;
		//static constexpr bool isAnalog;
		//static constexpr bool hasDigital;
		//static constexpr uint8_t bitmask;
		//static constexpr uint8_t timer;
	};
}
}

//Different definitions
#if defined(__AVR_ATmega48A__) || defined(__AVR_ATmega48PA__) \
	|| defined(__AVR_ATmega88A__) || defined(__AVR_ATmega88PA__) \
	|| defined(__AVR_ATmega168A__) || defined(__AVR_ATmega168PA__) \
	|| defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__)

#include "pin-defs/ATmegaX8.hpp"

#elif defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)

#include "pin-defs/ATtinyX5.hpp"

#endif

#endif