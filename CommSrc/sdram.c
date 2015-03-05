// sdram.c
#include "typeDef.h"
#include "LPC177x_8x.h"
#include "system_LPC177x_8x.h"
#include "net_misc.h"
#include "sdram.h"

#define EMC_NS2CLK(ns, nsPerClk)	((ns + nsPerClk - 1) / nsPerClk)

void _DelayMs(int ms) 
{
  LPC_TIM0->TCR = 0x02;  // Reset timer
  LPC_TIM0->PR  = 0x00;  // Set prescaler to zero
  LPC_TIM0->MR0 = ms * (SystemCoreClock / (LPC_SC->PCLKSEL & 0x1F) / 1000 - 1);
  LPC_TIM0->IR  = 0xFF;  // Reset all interrrupts
  LPC_TIM0->MCR = 0x04;  // Stop timer on match
  LPC_TIM0->TCR = 0x01;  // Start timer
  //
  // Wait until delay time has elapsed
  //
  while (LPC_TIM0->TCR & 1);
}
#ifdef USE_GUI_X_Delay
#define mS_Delay _DelayMs
#endif
//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------

// 	<h> Misc Config
//		<o.0..1>		EMCDynamicRASCAS0.RAS
//			<1=> 1 CCLK
//			<2=> 2 CCLK
//			<3=> 3 CCLK
//		<i> Set RAS latency for nCS0
//		<o.8..9>		EMCDynamicRASCAS0.CAS
//			<1=> 1 CCLK
//			<2=> 2 CCLK
//			<3=> 3 CCLK
//		<i> Set CAS latency for nCS0
#define MDKCFG_RASCAS0VAL	0x00000303
//		<o.0..1>		EMCDynamicRASCAS1.RAS
//			<1=> 1 CCLK
//			<2=> 2 CCLK
//			<3=> 3 CCLK
//		<i> Set RAS latency for nCS1
//		<o.8..9>		EMCDynamicRASCAS1.CAS
//			<1=> 1 CCLK
//			<2=> 2 CCLK
//			<3=> 3 CCLK
//		<i> Set CAS latency for nCS1

#define MDKCFG_RASCAS1VAL	0x00000303

//	</h>
//*** <<< end of configuration section >>>    ***

void emc_init(void)
{
	LPC_IOCON->P3_0 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // D0 @ P3.0
	LPC_IOCON->P3_1 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // D1 @ P3.1
    LPC_IOCON->P3_2 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // D2 @ P3.2
	LPC_IOCON->P3_3 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // D3 @ P3.3

    LPC_IOCON->P3_4 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // D4 @ P3.4
    LPC_IOCON->P3_5 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // D5 @ P3.5
    LPC_IOCON->P3_6 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // D6 @ P3.6
    LPC_IOCON->P3_7 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // D7 @ P3.7

    LPC_IOCON->P3_8 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // D8 @ P3.8
    LPC_IOCON->P3_9 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // D9 @ P3.9
    LPC_IOCON->P3_10 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // D10 @ P3.10
    LPC_IOCON->P3_11 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // D11 @ P3.11

    LPC_IOCON->P3_12 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // D12 @ P3.12
    LPC_IOCON->P3_13 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // D13 @ P3.13
    LPC_IOCON->P3_14 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // D14 @ P3.14
    LPC_IOCON->P3_15 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // D15 @ P3.15

    LPC_IOCON->P3_16 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // D16 @ P3.16
    LPC_IOCON->P3_17 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // D17 @ P3.17
    LPC_IOCON->P3_18 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // D18 @ P3.18
    LPC_IOCON->P3_19 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // D19 @ P3.19

    LPC_IOCON->P3_20 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // D20 @ P3.20
    LPC_IOCON->P3_21 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // D21 @ P3.21
    LPC_IOCON->P3_22 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // D22 @ P3.22
    LPC_IOCON->P3_23 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // D23 @ P3.23

    LPC_IOCON->P3_24 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // D24 @ P3.24
    LPC_IOCON->P3_25 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // D25 @ P3.25
    LPC_IOCON->P3_26 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // D26 @ P3.26
    LPC_IOCON->P3_27 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // D27 @ P3.27

    LPC_IOCON->P3_28 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // D28 @ P3.28
    LPC_IOCON->P3_29 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // D29 @ P3.29
    LPC_IOCON->P3_30 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // D30 @ P3.30
    LPC_IOCON->P3_31 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // D31 @ P3.31

    LPC_IOCON->P4_0 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // A0 @ P4.0
    LPC_IOCON->P4_1 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // A1 @ P4.1
    LPC_IOCON->P4_2 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // A2 @ P4.2
    LPC_IOCON->P4_3 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // A3 @ P4.3

    LPC_IOCON->P4_4 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // A4 @ P4.4
    LPC_IOCON->P4_5 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // A5 @ P4.5
    LPC_IOCON->P4_6 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // A6 @ P4.6
    LPC_IOCON->P4_7 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // A7 @ P4.7

    LPC_IOCON->P4_8 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // A8 @ P4.8
    LPC_IOCON->P4_9 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // A9 @ P4.9
    LPC_IOCON->P4_10 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // A10 @ P4.10
    LPC_IOCON->P4_11 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // A11 @ P4.11

    LPC_IOCON->P4_12 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // A12 @ P4.12
    LPC_IOCON->P4_13 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // A13 @ P4.13
    LPC_IOCON->P4_14 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // A14 @ P4.14
    LPC_IOCON->P4_15 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // A15 @ P4.15

    LPC_IOCON->P4_16 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // A16 @ P4.16
    LPC_IOCON->P4_17 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // A17 @ P4.17
    LPC_IOCON->P4_18 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // A18 @ P4.18
    LPC_IOCON->P4_19 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // A19 @ P4.19

    LPC_IOCON->P4_20 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // A20 @ P4.20
    LPC_IOCON->P4_21 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // A21 @ P4.21
    LPC_IOCON->P4_22 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // A22 @ P4.22
    LPC_IOCON->P4_23 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // A23 @ P4.23

	LPC_IOCON->P4_25 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // WEN @ P4.25
	LPC_IOCON->P4_24 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // OEN @ P4.24

#if 0
    LPC_IOCON->P4_26 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // BLSN[0] @ P4.26
    LPC_IOCON->P4_27 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // BLSN[1] @ P4.27
    LPC_IOCON->P4_28 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // BLSN[2] @ P4.28
    LPC_IOCON->P4_29 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // BLSN[3] @ P4.29
#endif
	LPC_IOCON->P4_30 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // CSN[0] @ P4.30
//	LPC_IOCON->P4_31 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // CSN[1] @ P4.31
//	LPC_IOCON->P2_14 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // CSN[2] @ P2.14
//	LPC_IOCON->P2_15 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // CSN[3] @ P2.15

#if 1
    LPC_IOCON->P2_16 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // CASN @ P2.16
    LPC_IOCON->P2_17 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // RASN @ P2.17
    LPC_IOCON->P2_18 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // CLK[0] @ P2.18
    LPC_IOCON->P2_19 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // CLK[1] @ P2.19

    LPC_IOCON->P2_20 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // DYCSN[0] @ P2.20
    LPC_IOCON->P2_21 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // DYCSN[1] @ P2.21
    LPC_IOCON->P2_22 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // DYCSN[2] @ P2.22
    LPC_IOCON->P2_23 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // DYCSN[3] @ P2.23

    LPC_IOCON->P2_24 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // CKE[0] @ P2.24

//  LPC_IOCON->P2_25 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // CKE[1] @ P2.25
    LPC_IOCON->P2_26 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // CKE[2] @ P2.26
    LPC_IOCON->P2_27 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // CKE[3] @ P2.27

    LPC_IOCON->P2_28 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // DQM[0] @ P2.28
    LPC_IOCON->P2_29 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // DQM[1] @ P2.29
    LPC_IOCON->P2_30 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // DQM[2] @ P2.30
    LPC_IOCON->P2_31 = (1<<0 | 0<<3 | 0<<5 | 1<<9); // DQM[3] @ P2.31
#endif
}

__asm void fastClearRam(void *beg, U32 sz)
{
	PUSH {R2-R9}
	MOVS R2, #0
	MOVS R3, #0
	MOVS R4, #0
	MOVS R5, #0
	MOVS R6, #0
	MOVS R7, #0
	MOVS R8, #0
	MOVS R9, #0
	LSR R1, #0x05
	STM R0!, {R2-R9}
	SUBS R1, #0x01
	BCS .-6
	POP {R2-R9}
	BX LR
}

void sdram_init(void)
{
    U32 i, dwtemp = dwtemp;
	U32 mhz, nsPerClk;
    U16 wtemp = wtemp;
// Enable External Memory Controller power/clock
	LPC_SC->PCONP |= 0x00000800;
	LPC_SC->EMCDLYCTL = 0x00001010;
    LPC_EMC->Control = 0x00000001;
    LPC_EMC->Config = 0x00000000;
	emc_init();

	mhz = SystemCoreClock / 1000000;
	if (LPC_SC->EMCCLKSEL) mhz >>= 1;
	nsPerClk = 1000 / mhz;
    LPC_EMC->DynamicRP         = EMC_NS2CLK(20, nsPerClk); /* 20ns,  */
    LPC_EMC->DynamicRAS        = /*EMC_NS2CLK(42, nsPerClk);*/ 15; /* 42ns to 100K ns,  */
    LPC_EMC->DynamicSREX       = 1 - 1; /* tSRE, 1clk, */
    LPC_EMC->DynamicAPR        = 2 - 1; /* Not found!!! Estimated as 2clk, */  
    LPC_EMC->DynamicDAL        = EMC_NS2CLK(20, nsPerClk) + 2; /* tDAL = tRP + tDPL = 20ns + 2clk  */
    LPC_EMC->DynamicWR         = 2 - 1; /* 2CLK,  */
    LPC_EMC->DynamicRC         = EMC_NS2CLK(63, nsPerClk); /* H57V2562GTR-75C tRC=63ns(min)*/
    LPC_EMC->DynamicRFC        = EMC_NS2CLK(63, nsPerClk); /* H57V2562GTR-75C tRFC=tRC */
    LPC_EMC->DynamicXSR        = 0x0000000F; /* exit self-refresh to active, 不知道，设为最久  */
    LPC_EMC->DynamicRRD        = EMC_NS2CLK(63, nsPerClk); /* 3clk, tRRD=15ns(min) */
    LPC_EMC->DynamicMRD        = 2 - 1; /* 2clk, tMRD=2clk(min) */		

	LPC_EMC->DynamicReadConfig = 0x00000001; /* Command delayed strategy, using EMCCLKDELAY */
    /* H57V2562GTR-75C: tCL=3CLK, tRCD=20ns(min), 3 CLK=24ns */
    LPC_EMC->DynamicRasCas0    = MDKCFG_RASCAS0VAL; 

    /* For Manley lpc1778 SDRAM: H57V2562GTR-75C, 256Mb, 16Mx16, 4 banks, row=13, column=9 */
#ifdef SDRAM_CONFIG_16BIT
    LPC_EMC->DynamicConfig0    = 0x680; /* 256Mb, 16Mx16, 4 banks, row=13, column=9, RBC */
#elif defined SDRAM_CONFIG_32BIT
    LPC_EMC->DynamicConfig0	= 0x4680; /* 256Mb, 16Mx16, 4 banks, row=13, column=9, RBC */
#endif
    mS_Delay(100);

    LPC_EMC->DynamicControl    = 0x00000183; /* Issue NOP command */
    mS_Delay(200);							  /* wait 200ms */

    LPC_EMC->DynamicControl    = 0x00000103; /* Issue PALL command */

    LPC_EMC->DynamicRefresh    = 0x00000002; /* ( n * 16 ) -> 32 clock cycles */
    for(i = 0; i < 0x80; i++);	              /* wait 128 AHB clock cycles */
    /* 64ms/8192=7.8125us, nx16x8.33ns<7.8125us, n<58.6*/
	wtemp = 64000000 / (1 << 13);
	wtemp -= 16;
	wtemp >>= 4;
	wtemp = wtemp * mhz / 1000;
    LPC_EMC->DynamicRefresh    = wtemp;

    LPC_EMC->DynamicControl    = 0x00000083; /* Issue MODE command */

#ifdef SDRAM_CONFIG_16BIT

    wtemp = *((volatile uint16_t *)(SDRAM_BASE | (0x33<<12))); /* 8 burst, 3 CAS latency */
#elif defined SDRAM_CONFIG_32BIT
    dwtemp = *((volatile uint32_t *)(SDRAM_BASE | (0x32<<13)));	/* 4 burst, 3 CAS latency */
#endif

    LPC_EMC->DynamicControl    = 0x00000000; /* Issue NORMAL command */

    LPC_EMC->DynamicConfig0 |= 0x80000; /* enable buffer */
	mS_Delay(1);
#ifndef SDRAM_NO_INIT
	fastClearRam((void *)SDRAM_BASE, SDRAM_SIZE);
#endif 
}

#ifdef SDRAM_TEST
int sdram_test(void)
{
    volatile U32 *wr_ptr;
    volatile U16 *short_wr_ptr;
    volatile U8 *ch_wr_ptr;
    U32 data;
    U32 i, j;

    wr_ptr = (U32 *)SDRAM_BASE;
    short_wr_ptr = (U16 *)wr_ptr;
// Clear content before 16 bit access test
	for (i = 0; i < SDRAM_SIZE/4; i++)
		*wr_ptr++ = 0;

// 16 bit write
    for (i = 0; i < SDRAM_SIZE/0x40000; i++) {
		for (j = 0; j < 0x10000; j++) {
			*short_wr_ptr++ = (i + j);
            *short_wr_ptr++ = (i + j) + 1;
		}
	}

// Verifying
	wr_ptr = (U32 *)SDRAM_BASE;
	for (i = 0; i < SDRAM_SIZE/0x40000; i++) {
		for (j = 0; j < 0x10000; j++) {
			data = *wr_ptr;
			if (data != (((((i + j) + 1) & 0xFFFF) << 16) | ((i + j) & 0xFFFF)))
                return 0x0;
			wr_ptr++;
		}
	}
	
	ch_wr_ptr = (U8 *)SDRAM_BASE;
	data = 0;
	for (i = 0; i < SDRAM_SIZE/0x40000; i++) {
		*ch_wr_ptr++ = data++;
	}	
	return 0x1;
}
#endif
