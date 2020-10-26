/* detail/registers/ATtinyX5.h
 *
 * Copyright (C) 2018 Jan Rogall
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 * Generated from iotn441.h
 */

#ifndef MICROPIN_DETAIL_REGISTERS_ATTINYX41_INCLUDED
#define MICROPIN_DETAIL_REGISTERS_ATTINYX41_INCLUDED

namespace MicroPin
{
    constexpr Register8 rADCSRB {0x04 + sfrOffset};
    constexpr Register8 rADCSRA {0x05 + sfrOffset};
    constexpr Register16 rADC {0x06 + sfrOffset};
    constexpr Register16 rADCW {0x06 + sfrOffset};
    constexpr Register8 rADCL {0x06 + sfrOffset};
    constexpr Register8 rADCH {0x07 + sfrOffset};
    constexpr Register8 rADMUXB {0x08 + sfrOffset};
    constexpr Register8 rADMUXA {0x09 + sfrOffset};
    constexpr Register8 rACSR0A {0x0a + sfrOffset};
    constexpr Register8 rACSR0B {0x0b + sfrOffset};
    constexpr Register8 rACSR1A {0x0c + sfrOffset};
    constexpr Register8 rACSR1B {0x0d + sfrOffset};
    constexpr Register8 rTIFR1 {0x0e + sfrOffset};
    constexpr Register8 rTIMSK1 {0x0f + sfrOffset};
    constexpr Register8 rTIFR2 {0x10 + sfrOffset};
    constexpr Register8 rTIMSK2 {0x11 + sfrOffset};
    constexpr Register8 rPCMSK0 {0x12 + sfrOffset};
    constexpr Register8 rGPIOR0 {0x13 + sfrOffset};
    constexpr Register8 rGPIOR1 {0x14 + sfrOffset};
    constexpr Register8 rGPIOR2 {0x15 + sfrOffset};
    constexpr Register8 rPINB {0x16 + sfrOffset};
    constexpr Register8 rDDRB {0x17 + sfrOffset};
    constexpr Register8 rPORTB {0x18 + sfrOffset};
    constexpr Register8 rPINA {0x19 + sfrOffset};
    constexpr Register8 rDDRA {0x1a + sfrOffset};
    constexpr Register8 rPORTA {0x1b + sfrOffset};
    constexpr Register8 rEECR {0x1c + sfrOffset};
    constexpr Register8 rEEDR {0x1d + sfrOffset};
    constexpr Register16 rEEAR {0x1e + sfrOffset};
    constexpr Register8 rEEARL {0x1e + sfrOffset};
    constexpr Register8 rEEARH {0x1f + sfrOffset};
    constexpr Register8 rPCMSK1 {0x20 + sfrOffset};
    constexpr Register8 rWDTCSR {0x21 + sfrOffset};
    constexpr Register8 rTCCR1C {0x22 + sfrOffset};
    constexpr Register8 rGTCCR {0x23 + sfrOffset};
    constexpr Register16 rICR1 {0x24 + sfrOffset};
    constexpr Register8 rICR1L {0x24 + sfrOffset};
    constexpr Register8 rICR1H {0x25 + sfrOffset};
    constexpr Register16 rOCR1B {0x28 + sfrOffset};
    constexpr Register8 rOCR1BL {0x28 + sfrOffset};
    constexpr Register8 rOCR1BH {0x29 + sfrOffset};
    constexpr Register16 rOCR1A {0x2a + sfrOffset};
    constexpr Register8 rOCR1AL {0x2a + sfrOffset};
    constexpr Register8 rOCR1AH {0x2b + sfrOffset};
    constexpr Register16 rTCNT1 {0x2c + sfrOffset};
    constexpr Register8 rTCNT1L {0x2c + sfrOffset};
    constexpr Register8 rTCNT1H {0x2d + sfrOffset};
    constexpr Register8 rTCCR1B {0x2e + sfrOffset};
    constexpr Register8 rTCCR1A {0x2f + sfrOffset};
    constexpr Register8 rTCCR0A {0x30 + sfrOffset};
    constexpr Register8 rTCNT0 {0x32 + sfrOffset};
    constexpr Register8 rTCCR0B {0x33 + sfrOffset};
    constexpr Register8 rMCUSR {0x34 + sfrOffset};
    constexpr Register8 rMCUCR {0x35 + sfrOffset};
    constexpr Register8 rOCR0A {0x36 + sfrOffset};
    constexpr Register8 rSPMCSR {0x37 + sfrOffset};
    constexpr Register8 rTIFR0 {0x38 + sfrOffset};
    constexpr Register8 rTIMSK0 {0x39 + sfrOffset};
    constexpr Register8 rGIFR {0x3a + sfrOffset};
    constexpr Register8 rGIMSK {0x3b + sfrOffset};
    constexpr Register8 rOCR0B {0x3c + sfrOffset};
    constexpr Register8 rDIDR0 {0x60};
    constexpr Register8 rDIDR1 {0x61};
    constexpr Register8 rPUEB {0x62};
    constexpr Register8 rPUEA {0x63};
    constexpr Register8 rPORTCR {0x64};
    constexpr Register8 rREMAP {0x65};
    constexpr Register8 rTOCPMCOE {0x66};
    constexpr Register8 rTOCPMSA0 {0x67};
    constexpr Register8 rTOCPMSA1 {0x68};
    constexpr Register8 rPHDE {0x6a};
    constexpr Register8 rPRR {0x70};
    constexpr Register8 rCCP {0x71};
    constexpr Register8 rCLKCR {0x72};
    constexpr Register8 rCLKPR {0x73};
    constexpr Register8 rOSCCAL0 {0x74};
    constexpr Register8 rOSCTCAL0A {0x75};
    constexpr Register8 rOSCTCAL0B {0x76};
    constexpr Register8 rOSCCAL1 {0x77};
    constexpr Register8 rUDR0 {0x80};
    constexpr Register16 rUBRR0 {0x81};
    constexpr Register8 rUBRR0L {0x81};
    constexpr Register8 rUBRR0H {0x82};
    constexpr Register8 rUCSR0D {0x83};
    constexpr Register8 rUCSR0C {0x84};
    constexpr Register8 rUCSR0B {0x85};
    constexpr Register8 rUCSR0A {0x86};
    constexpr Register8 rUDR1 {0x90};
    constexpr Register16 rUBRR1 {0x91};
    constexpr Register8 rUBRR1L {0x91};
    constexpr Register8 rUBRR1H {0x92};
    constexpr Register8 rUCSR1D {0x93};
    constexpr Register8 rUCSR1C {0x94};
    constexpr Register8 rUCSR1B {0x95};
    constexpr Register8 rUCSR1A {0x96};
    constexpr Register8 rTWSD {0xa0};
    constexpr Register8 rTWSAM {0xa1};
    constexpr Register8 rTWSA {0xa2};
    constexpr Register8 rTWSSRA {0xa3};
    constexpr Register8 rTWSCRB {0xa4};
    constexpr Register8 rTWSCRA {0xa5};
    constexpr Register8 rSPDR {0xb0};
    constexpr Register8 rSPSR {0xb1};
    constexpr Register8 rSPCR {0xb2};
    constexpr Register16 rICR2 {0xc0};
    constexpr Register8 rICR2L {0xc0};
    constexpr Register8 rICR2H {0xc1};
    constexpr Register16 rOCR2B {0xc2};
    constexpr Register8 rOCR2BL {0xc2};
    constexpr Register8 rOCR2BH {0xc3};
    constexpr Register16 rOCR2A {0xc4};
    constexpr Register8 rOCR2AL {0xc4};
    constexpr Register8 rOCR2AH {0xc5};
    constexpr Register16 rTCNT2 {0xc6};
    constexpr Register8 rTCNT2L {0xc6};
    constexpr Register8 rTCNT2H {0xc7};
    constexpr Register8 rTCCR2C {0xc8};
    constexpr Register8 rTCCR2B {0xc9};
    constexpr Register8 rTCCR2A {0xca};

    // SREG defined elsewhere, added manually
    constexpr Register8 rSREG {0x3F + sfrOffset};

    // Manually added bits which are used
    constexpr Bit bCOM0A1 = 7_bit;
    constexpr Bit bCOM0B1 = 5_bit;
    constexpr Bit bCOM1A1 = 7_bit;
    constexpr Bit bCOM1B1 = 5_bit;
    constexpr Bit bCOM2A1 = 7_bit;
    constexpr Bit bCOM2B1 = 5_bit;
    constexpr Bit bADEN = 7_bit;
    constexpr Bit bADSC = 6_bit;

    // Dirty fix for analogRead
    constexpr Register8 rADMUX = rADMUXA;
} // namespace MicroPin

#endif
