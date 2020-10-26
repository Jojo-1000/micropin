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
    constexpr Register8 rPINB{0x03 + sfrOffset};
    constexpr Register8 rDDRB{0x04 + sfrOffset};
    constexpr Register8 rPORTB{0x05 + sfrOffset};
    constexpr Register8 rPINC{0x06 + sfrOffset};
    constexpr Register8 rDDRC{0x07 + sfrOffset};
    constexpr Register8 rPORTC{0x08 + sfrOffset};
    constexpr Register8 rPIND{0x09 + sfrOffset};
    constexpr Register8 rDDRD{0x0a + sfrOffset};
    constexpr Register8 rPORTD{0x0b + sfrOffset};
    constexpr Register8 rTIFR0{0x15 + sfrOffset};
    constexpr Register8 rTIFR1{0x16 + sfrOffset};
    constexpr Register8 rTIFR2{0x17 + sfrOffset};
    constexpr Register8 rPCIFR{0x1b + sfrOffset};
    constexpr Register8 rEIFR{0x1c + sfrOffset};
    constexpr Register8 rEIMSK{0x1d + sfrOffset};
    constexpr Register8 rGPIOR0{0x1e + sfrOffset};
    constexpr Register8 rEECR{0x1f + sfrOffset};
    constexpr Register8 rEEDR{0x20 + sfrOffset};
    constexpr Register16 rEEAR{0x21 + sfrOffset};
    constexpr Register8 rEEARL{0x21 + sfrOffset};
    constexpr Register8 rEEARH{0x22 + sfrOffset};
    constexpr Register8 rGTCCR{0x23 + sfrOffset};

    constexpr Register8 rTCCR0A{0x24 + sfrOffset};
    constexpr Bit bCOM0A1 = 7_bit;
    constexpr Bit bCOM0B1 = 5_bit;
    constexpr Register8 rTCCR0B{0x25 + sfrOffset};
    constexpr Register8 rTCNT0{0x26 + sfrOffset};
    constexpr Register8 rOCR0A{0x27 + sfrOffset};
    constexpr Register8 rOCR0B{0x28 + sfrOffset};
    constexpr Register8 rGPIOR1{0x2a + sfrOffset};
    constexpr Register8 rGPIOR2{0x2b + sfrOffset};
    constexpr Register8 rSPCR{0x2c + sfrOffset};
    constexpr Register8 rSPSR{0x2d + sfrOffset};
    constexpr Register8 rSPDR{0x2e + sfrOffset};
    constexpr Register8 rACSR{0x30 + sfrOffset};
    constexpr Register8 rSMCR{0x33 + sfrOffset};
    constexpr Register8 rMCUSR{0x34 + sfrOffset};
    constexpr Register8 rMCUCR{0x35 + sfrOffset};
    constexpr Register8 rSPMCSR{0x37 + sfrOffset};
    constexpr Register8 rSREG{0x3F + sfrOffset};
    constexpr Register8 rWDTCSR{0x60};
    constexpr Register8 rCLKPR{0x61};
    constexpr Register8 rPRR{0x64};
    constexpr Register8 rOSCCAL{0x66};
    constexpr Register8 rPCICR{0x68};
    constexpr Register8 rEICRA{0x69};
    constexpr Register8 rPCMSK0{0x6b};
    constexpr Register8 rPCMSK1{0x6c};
    constexpr Register8 rPCMSK2{0x6d};
    constexpr Register8 rTIMSK0{0x6e};
    constexpr Register8 rTIMSK1{0x6f};
    constexpr Register8 rTIMSK2{0x70};
    constexpr Register16 rADC{0x78};
    constexpr Register16 rADCW{0x78};
    constexpr Register8 rADCL{0x78};
    constexpr Register8 rADCH{0x79};
    constexpr Register8 rADCSRA{0x7a};
    constexpr Bit bADEN = 7_bit;
    constexpr Bit bADSC = 6_bit;

    constexpr Register8 rADCSRB{0x7b};
    constexpr Register8 rADMUX{0x7C};
    constexpr Register8 rDIDR0{0x7e};
    constexpr Register8 rDIDR1{0x7f};

    constexpr Register8 rTCCR1A{0x80};
    constexpr Bit bCOM1A1 = 7_bit;
    constexpr Bit bCOM1B1 = 5_bit;
    
    constexpr Register8 rTCCR1B{0x81};
    constexpr Register8 rTCCR1C{0x82};
    constexpr Register16 rTCNT1{0x84};
    constexpr Register8 rTCNT1L{0x84};
    constexpr Register8 rTCNT1H{0x85};
    constexpr Register16 rICR1{0x86};
    constexpr Register8 rICR1L{0x86};
    constexpr Register8 rICR1H{0x87};
    constexpr Register16 rOCR1A{0x88};
    constexpr Register8 rOCR1AL{0x88};
    constexpr Register8 rOCR1AH{0x89};
    constexpr Register16 rOCR1B{0x8a};
    constexpr Register8 rOCR1BL{0x8a};
    constexpr Register8 rOCR1BH{0x8b};
    constexpr Register8 rTCCR2A{0xb0};
    constexpr Bit bCOM2A1 = 7_bit;
    constexpr Bit bCOM2B1 = 5_bit;
    constexpr Register8 rTCNT2{0xb2};
    constexpr Register8 rOCR2A{0xb3};
    constexpr Register8 rOCR2B{0xb4};
    constexpr Register8 rASSR{0xb6};
    constexpr Register8 rTWBR{0xb8};
    constexpr Register8 rTWSR{0xb9};
    constexpr Register8 rTWAR{0xba};
    constexpr Register8 rTWDR{0xbb};
    constexpr Register8 rTWCR{0xbc};
    constexpr Register8 rTWAMR{0xbd};
    constexpr Register8 rUCSR0A{0xc0};
    constexpr Register8 rUCSR0B{0xc1};
    constexpr Register8 rUCSR0C{0xc2};
    constexpr Register16 rUBRR0{0xc4};
    constexpr Register8 rUBRR0L{0xc4};
    constexpr Register8 rUBRR0H{0xc5};
    constexpr Register8 rUDR0{0xc6};
}

#endif
