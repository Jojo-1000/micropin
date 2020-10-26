/* RegisterDefinitions.h
 *
 * Copyright (C) 2018 Jan Rogall
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */


#ifndef MICROPIN_REGISTERDEFINITIONS_INCLUDED
#define MICROPIN_REGISTERDEFINITIONS_INCLUDED

#include "Register.hpp"

//Only some implemented yet
#if defined(__AVR_ATmega48A__) || defined(__AVR_ATmega48PA__) \
    || defined(__AVR_ATmega88A__) || defined(__AVR_ATmega88PA__) \
    || defined(__AVR_ATmega168A__) || defined(__AVR_ATmega168PA__) \
    || defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__)
#   include "detail/registers/ATmegaX8.hpp"
#elif defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
#   include "detail/registers/ATtinyX5.hpp"
#elif defined(__AVR_ATtiny441__) || defined(__AVR_ATtiny841)
#   include "detail/registers/ATtinyX41.hpp"
#else
#   error "Unsupported device"
#endif

#endif
