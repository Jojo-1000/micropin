/* detail/registers/ATmegaX8.h
*
* Copyright (C) 2018 Jan Rogall
*
* This software may be modified and distributed under the terms
* of the MIT license.  See the LICENSE file for details.
*/

#ifndef MICROPIN_DETAIL_REGISTERS_ATMEGAX8_INCLUDED
#define MICROPIN_DETAIL_REGISTERS_ATMEGAX8_INCLUDED

namespace MicroPin
{
    //Registers are prefixed with r and Bits with b to avoid conflicts with avr #defines

    constexpr Register8 rPINB{0x23};
    constexpr Register8 rDDRB{0x24};
    constexpr Register8 rPORTB{0x25};

    constexpr Register8 rPINC{0x26};
    constexpr Register8 rDDRC{0x27};
    constexpr Register8 rPORTC{0x28};

    constexpr Register8 rPIND{0x29};
    constexpr Register8 rDDRD{0x2A};
    constexpr Register8 rPORTD{0x2B};


    constexpr Register8 rTCCR0A{0x44};
    constexpr Bit bCOM0A1 = 7_bit;
    constexpr Bit bCOM0B1 = 5_bit;

    constexpr Register8 rOCR0A{0x47};
    constexpr Register8 rOCR0B{0x48};

    constexpr Register8 rSREG{0x5F};

    constexpr Register16 rADC{0x78};
    constexpr Register16 rADCW{0x78};
    constexpr Register8 rADCL{0x78};
    constexpr Register8 rADCH{0x79};

    constexpr Register8 rADCSRA{0x7A};
    constexpr Bit bADEN = 7_bit;
    constexpr Bit bADSC = 6_bit;

    constexpr Register8 rADMUX{0x7C};


    constexpr Register8 rTCCR1A{0x80};
    constexpr Bit bCOM1A1 = 7_bit;
    constexpr Bit bCOM1B1 = 5_bit;

    constexpr Register16 rOCR1A{0x88};
    constexpr Register16 rOCR1B{0x8A};

    constexpr Register8 rTCCR2A{0xB0};
    constexpr Bit bCOM2A1 = 7_bit;
    constexpr Bit bCOM2B1 = 5_bit;

    constexpr Register8 rOCR2A{0xB3};
    constexpr Register8 rOCR2B{0xB4};
}

#endif
