/* detail/ADC.h
 *
 * Copyright (C) 2018 Jan Rogall
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#ifndef MICROPIN_DETAIL_ADC_INCLUDED
#define MICROPIN_DETAIL_ADC_INCLUDED

namespace MicroPin
{
namespace detail
{
    //clock prescaler 6 => 64, so the frequency is 125 KHz
    constexpr uint8_t prescaleADC = 0x06;
}
}

#endif
