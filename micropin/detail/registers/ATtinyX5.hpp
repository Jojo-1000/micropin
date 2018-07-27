/* detail/registers/ATtinyX5.h
 *
 * Copyright (C) 2018 Jan Rogall
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#ifndef MICROPIN_DETAIL_REGISTERS_ATTINYX5_INCLUDED
#define MICROPIN_DETAIL_REGISTERS_ATTINYX5_INCLUDED

namespace MicroPin
{
    //Registers are prefixed with r and Bits with b to avoid conflicts with avr #defines

    constexpr Register8 rPINB{0x16};
    constexpr Register8 rDDRB{0x17};
    constexpr Register8 rPORTB{0x18};
    
    constexpr Register8 rTCCR0A{0x2A};
    constexpr Bit bCOM0A1 = 7_bit;
    constexpr Bit bCOM0B1 = 5_bit;

    constexpr Register8 rOCR0A{0x29};
    constexpr Register8 rOCR0B{0x28};

    constexpr Register8 rSREG{0x3F};

    constexpr Register16 rADCW{0x04};
    constexpr Register8 rADCL{0x04};
    constexpr Register8 rADCH{0x05};

    constexpr Register8 rADCSRA{0x7A};
    constexpr Bit bADEN = 7_bit;
    constexpr Bit bADSC = 6_bit;

    constexpr Register8 rADMUX{0x07};


    constexpr Register8 rTCCR1{0x30};
    constexpr Bit bCOM1A1 = 5_bit;

    constexpr Register8 rGTCCR{0x2C};
    constexpr Bit bCOM1B1 = 5_bit;

    constexpr Register16 rOCR1A{0x2E};
    constexpr Register16 rOCR1B{0x2B};
}

#endif