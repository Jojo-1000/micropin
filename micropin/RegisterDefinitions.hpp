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
#if defined (__AVR_ATmega328P__)
#  include "detail/Registers/ATmegaX8.hpp"
#endif

#endif