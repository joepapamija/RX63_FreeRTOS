/************************************************************************/
/*    File Version: V1.00                                               */
/*    Date Generated: 08/07/2013                                        */
/************************************************************************/

#include "stdint.h"
#include "iodefine.h"
#include "yrdkrx62ndef.h"

#ifdef __cplusplus
extern "C" {
#endif
extern void HardwareSetup(void);
#ifdef __cplusplus
}
#endif

static void operating_frequency_set (void);
static void clock_source_select (void);

void HardwareSetup(void)
{
unsigned long sckcr = 0;

#if 1
	SYSTEM.PRCR.WORD = 0xA50B;			/* Protect off */
	MPC.PWPR.BIT.B0WI = 0 ;     		/* Unlock protection register */
	MPC.PWPR.BIT.PFSWE = 1 ;    		/* Unlock MPC registers */
#endif

	operating_frequency_set();
}


#define BSP_CFG_FCK_DIV                 (4)
#define BSP_CFG_ICK_DIV                 (2)
#define BSP_CFG_BCK_DIV                 (8)
#define BSP_CFG_PCKA_DIV                (4)
#define BSP_CFG_PCKB_DIV                (4)
#define BSP_CFG_IEBCK_DIV               (8)
#define BSP_CFG_UCK_DIV                 (4)
#define BSP_CFG_CLOCK_SOURCE            (4)
#define BSP_CFG_PLL_DIV                 (1)
#define BSP_CFG_PLL_MUL                 (16)

/***********************************************************************************************************************
* Function name: operating_frequency_set
* Description  : Configures the clock settings for each of the device clocks
* Arguments    : none
* Return value : none
***********************************************************************************************************************/
static void operating_frequency_set (void)
{
    /* Used for constructing value to write to SCKCR register. */
    uint32_t temp_clock = 0;

    /*
    Default settings:
    Clock Description              Frequency
    ----------------------------------------
    Input Clock Frequency............  12 MHz
    PLL frequency (x16).............. 192 MHz
    Internal Clock Frequency.........  96 MHz
    Peripheral Clock Frequency.......  48 MHz
    USB Clock Frequency..............  48 MHz
    External Bus Clock Frequency.....  24 MHz */

    /* Protect off. */
    SYSTEM.PRCR.WORD = 0xA50B;

    /* Select the clock based upon user's choice. */
    clock_source_select();

    /* Figure out setting for FCK bits. */
#if   BSP_CFG_FCK_DIV == 1
    /* Do nothing since FCK bits should be 0. */
#elif BSP_CFG_FCK_DIV == 2
    temp_clock |= 0x10000000;
#elif BSP_CFG_FCK_DIV == 4
    temp_clock |= 0x20000000;
#elif BSP_CFG_FCK_DIV == 8
    temp_clock |= 0x30000000;
#elif BSP_CFG_FCK_DIV == 16
    temp_clock |= 0x40000000;
#elif BSP_CFG_FCK_DIV == 32
    temp_clock |= 0x50000000;
#elif BSP_CFG_FCK_DIV == 64
    temp_clock |= 0x60000000;
#else
    #error "Error! Invalid setting for BSP_CFG_FCK_DIV in r_bsp_config.h"
#endif

    /* Figure out setting for ICK bits. */
#if   BSP_CFG_ICK_DIV == 1
    /* Do nothing since ICK bits should be 0. */
#elif BSP_CFG_ICK_DIV == 2
    temp_clock |= 0x01000000;
#elif BSP_CFG_ICK_DIV == 4
    temp_clock |= 0x02000000;
#elif BSP_CFG_ICK_DIV == 8
    temp_clock |= 0x03000000;
#elif BSP_CFG_ICK_DIV == 16
    temp_clock |= 0x04000000;
#elif BSP_CFG_ICK_DIV == 32
    temp_clock |= 0x05000000;
#elif BSP_CFG_ICK_DIV == 64
    temp_clock |= 0x06000000;
#else
    #error "Error! Invalid setting for BSP_CFG_ICK_DIV in r_bsp_config.h"
#endif

    /* Figure out setting for BCK bits. */
#if   BSP_CFG_BCK_DIV == 1
    /* Do nothing since BCK bits should be 0. */
#elif BSP_CFG_BCK_DIV == 2
    temp_clock |= 0x00010000;
#elif BSP_CFG_BCK_DIV == 4
    temp_clock |= 0x00020000;
#elif BSP_CFG_BCK_DIV == 8
    temp_clock |= 0x00030000;
#elif BSP_CFG_BCK_DIV == 16
    temp_clock |= 0x00040000;
#elif BSP_CFG_BCK_DIV == 32
    temp_clock |= 0x00050000;
#elif BSP_CFG_BCK_DIV == 64
    temp_clock |= 0x00060000;
#else
    #error "Error! Invalid setting for BSP_CFG_BCK_DIV in r_bsp_config.h"
#endif

    /* Configure PSTOP1 bit for BCLK output. */
#if BSP_CFG_BCLK_OUTPUT == 0
    /* Set PSTOP1 bit */
    temp_clock |= 0x00800000;
#elif BSP_CFG_BCLK_OUTPUT == 1
    /* Clear PSTOP1 bit */
    temp_clock &= ~0x00800000;
#elif BSP_CFG_BCLK_OUTPUT == 2
    /* Clear PSTOP1 bit */
    temp_clock &= ~0x00800000;
    /* Set BCLK divider bit */
    SYSTEM.BCKCR.BIT.BCLKDIV = 1;
#else
    #error "Error! Invalid setting for BSP_CFG_BCLK_OUTPUT in r_bsp_config.h"
#endif

    /* Configure PSTOP0 bit for SDCLK output. */
#if BSP_CFG_SDCLK_OUTPUT == 0
    /* Set PSTOP0 bit */
    temp_clock |= 0x00400000;
#elif BSP_CFG_SDCLK_OUTPUT == 1
    /* Clear PSTOP0 bit */
    temp_clock &= ~0x00400000;
#else
    #error "Error! Invalid setting for BSP_CFG_SDCLK_OUTPUT in r_bsp_config.h"
#endif

    /* Figure out setting for PCKA bits. */
#if   BSP_CFG_PCKA_DIV == 1
    /* Do nothing since PCKA bits should be 0. */
#elif BSP_CFG_PCKA_DIV == 2
    temp_clock |= 0x00001000;
#elif BSP_CFG_PCKA_DIV == 4
    temp_clock |= 0x00002000;
#elif BSP_CFG_PCKA_DIV == 8
    temp_clock |= 0x00003000;
#elif BSP_CFG_PCKA_DIV == 16
    temp_clock |= 0x00004000;
#elif BSP_CFG_PCKA_DIV == 32
    temp_clock |= 0x00005000;
#elif BSP_CFG_PCKA_DIV == 64
    temp_clock |= 0x00006000;
#else
    #error "Error! Invalid setting for BSP_CFG_PCKA_DIV in r_bsp_config.h"
#endif

    /* Figure out setting for PCKB bits. */
#if   BSP_CFG_PCKB_DIV == 1
    /* Do nothing since PCKB bits should be 0. */
#elif BSP_CFG_PCKB_DIV == 2
    temp_clock |= 0x00000100;
#elif BSP_CFG_PCKB_DIV == 4
    temp_clock |= 0x00000200;
#elif BSP_CFG_PCKB_DIV == 8
    temp_clock |= 0x00000300;
#elif BSP_CFG_PCKB_DIV == 16
    temp_clock |= 0x00000400;
#elif BSP_CFG_PCKB_DIV == 32
    temp_clock |= 0x00000500;
#elif BSP_CFG_PCKB_DIV == 64
    temp_clock |= 0x00000600;
#else
    #error "Error! Invalid setting for BSP_CFG_PCKB_DIV in r_bsp_config.h"
#endif

    /* Bottom byte of SCKCR register must be set to 0x11 */
    temp_clock |= 0x00000011;

    /* Set SCKCR register. */
    SYSTEM.SCKCR.LONG = temp_clock;

    /* Re-init temp_clock to use to set SCKCR2. */
    temp_clock = 0;

    /* Figure out setting for IEBCK bits. */
#if   BSP_CFG_IEBCK_DIV == 2
    temp_clock |= 0x00000001;
#elif BSP_CFG_IEBCK_DIV == 4
    temp_clock |= 0x00000002;
#elif BSP_CFG_IEBCK_DIV == 6
    temp_clock |= 0x0000000C;
#elif BSP_CFG_IEBCK_DIV == 8
    temp_clock |= 0x00000003;
#elif BSP_CFG_IEBCK_DIV == 16
    temp_clock |= 0x00000004;
#elif BSP_CFG_IEBCK_DIV == 32
    temp_clock |= 0x00000005;
#elif BSP_CFG_IEBCK_DIV == 64
    temp_clock |= 0x00000006;
#else
    #error "Error! Invalid setting for BSP_CFG_IEBCK_DIV in r_bsp_config.h"
#endif

    /* Figure out setting for UCK bits. */
#if   BSP_CFG_UCK_DIV == 3
    temp_clock |= 0x00000020;
#elif BSP_CFG_UCK_DIV == 4
    temp_clock |= 0x00000030;
#else
    #error "Error! Invalid setting for BSP_CFG_UCK_DIV in r_bsp_config.h"
#endif

    /* Set SCKCR2 register. */
    SYSTEM.SCKCR2.WORD = (uint16_t)temp_clock;

    /* Choose clock source. Default for r_bsp_config.h is PLL. */
    SYSTEM.SCKCR3.WORD = ((uint16_t)BSP_CFG_CLOCK_SOURCE) << 8;

#if (BSP_CFG_CLOCK_SOURCE != 0)
    /* We can now turn LOCO off since it is not going to be used. */
    SYSTEM.LOCOCR.BYTE = 0x01;
#endif

    /* Protect on. */
    SYSTEM.PRCR.WORD = 0xA500;
}

/***********************************************************************************************************************
* Function name: clock_source_select
* Description  : Enables and disables clocks as chosen by the user. This function also implements the software delays
*                needed for the clocks to stabilize.
* Arguments    : none
* Return value : none
***********************************************************************************************************************/
static void clock_source_select (void)
{
    /* Declared volatile for software delay purposes. */
    volatile uint32_t i;

    /* The delay loops used below have been measured to take 86us per iteration. This has been verified using the
       Renesas RX Toolchain with optimizations set to 2, size priority. The same result was obtained using 2, speed
       priority. At this time the MCU is still running on the 125kHz LOCO. */

#if (BSP_CFG_CLOCK_SOURCE == 1)
    /* HOCO is chosen. Start it operating. */
    SYSTEM.HOCOCR.BYTE = 0x00;

    /* The delay period needed is to make sure that the HOCO has stabilized. According to Rev.1.00 of the RX63N's HW
       manual the delay period is tHOCOWT2 which is 2ms. A delay of 2.4ms has been used below to account for variations
       in the LOCO.
       2.4ms / 86us (per iteration) = 28 iterations */
    for(i = 0; i < 28; i++)
    {
        /* Wait 2.4ms. See comment above for why. */
        nop() ;
    }
#else
    /* HOCO is not chosen. */
    /* Stop the HOCO. */
    SYSTEM.HOCOCR.BYTE = 0x01;

    /* Turn off power to HOCO. */
    SYSTEM.HOCOPCR.BYTE = 0x01;
#endif

#if (BSP_CFG_CLOCK_SOURCE == 2)
    /* Main clock oscillator is chosen. Start it operating. */
    /* Wait 65,536 cycles * 12 MHz = 5.46 ms */
    SYSTEM.MOSCWTCR.BYTE = 0x0C;

    /* Set the main clock to operating. */
    SYSTEM.MOSCCR.BYTE = 0x00;

    /* The delay period needed is to make sure that the main clock has stabilized. This delay period is tMAINOSCWT in
       the HW manual and according to the Renesas Technical Update document TN-RX*-A021A/E this is defined as:
       n = Wait time selected by MOSCWTCR.MSTS[] bits
       tMAINOSC = Main clock oscillator start-up time. From referring to various vendors, a start-up time of 4ms appears
                  to be a common maximum. To be safe we will use 5ms.
       tMAINOSCWT = tMAINOSC + ((n+16384)/fMAIN)
       tMAINOSCWT = 5ms + ((65536 + 16384)/12MHz)
       tMAINOSCWT = 11.82ms
       A delay of 12ms has been used below to account for variations in the LOCO.
       12ms / 86us (per iteration) = 140 iterations */
    for(i = 0; i < 140; i++)
    {
        /* Wait 12ms. See comment above for why. */
        nop() ;
    }
#else
    /* Set the main clock to stopped. */
    SYSTEM.MOSCCR.BYTE = 0x01;
#endif

#if (BSP_CFG_CLOCK_SOURCE == 3)
    /* Sub-clock oscillator is chosen. Start it operating. */
    /* Wait 65,536 cycles * 32768Hz = 2s. This meets the timing requirement tSUBOSC which is 2 seconds. */
    SYSTEM.SOSCWTCR.BYTE = 0x0C;

    /* Set the sub-clock to operating. */
    SYSTEM.SOSCCR.BYTE = 0x00;

    /* The delay period needed is to make sure that the sub-clock has stabilized. According to Rev.1.00 of the RX63N's
       HW manual the delay period is tSUBOSCWT0 which is at minimum 1.8s and at maximum 2.6 seconds. We will use the
       maximum value to be safe.
       2.6s / 86us (per iteration) = 30233 iterations */
    for(i = 0; i < 30233; i++)
    {
        /* Wait 2.6s. See comment above for why. */
        nop() ;
    }
#else
    /* Set the sub-clock to stopped. */
    SYSTEM.SOSCCR.BYTE = 0x01;
#endif

#if (BSP_CFG_CLOCK_SOURCE == 4)
    /* PLL is chosen. Start it operating. Must start main clock as well since PLL uses it. */
    /* Wait 65,536 cycles * 12 MHz = 5.46 ms */
    SYSTEM.MOSCWTCR.BYTE = 0x0C;

    /* Set the main clock to operating. */
    SYSTEM.MOSCCR.BYTE = 0x00;

    /* PLL wait is 1,048,576 cycles * 192 MHz (12 MHz * 16) = 5.46 ms*/
    SYSTEM.PLLWTCR.BYTE = 0x0D;

    /* Set PLL Input Divisor. */
    SYSTEM.PLLCR.BIT.PLIDIV = BSP_CFG_PLL_DIV >> 1;

    /* Set PLL Multiplier. */
    SYSTEM.PLLCR.BIT.STC = BSP_CFG_PLL_MUL - 1;

    /* Set the PLL to operating. */
    SYSTEM.PLLCR2.BYTE = 0x00;

    /* The delay period needed is to make sure that the main clock and PLL have stabilized. This delay period is
       tPLLWT2 when the main clock has not been previously stabilized. According to the Renesas Technical Update
       document TN-RX*-A021A/E this delay is defined as:
       n = Wait time selected by PLLWTCR.PSTS[] bits
       tMAINOSC = Main clock oscillator start-up time. From referring to various vendors, a start-up time of 4ms appears
                  to be a common maximum. To be safe we will use 5ms.
       tPLLWT2 = tMAINOSC + tPLL1 + ((n + 131072)/fPLL)
       tPLLWT2 = 5ms + 500us + ((1048576 + 131072)/192MHz)
       tPLLWT2 = 11.64ms
       A delay of 12ms has been used below to account for variations in the LOCO.
       12ms / 86us (per iteration) = 140 iterations */
    for(i = 0; i < 140; i++)
    {
        /* Wait 12ms. See comment above for why. */
    	__asm volatile( "NOP" );
    }
#else
    /* Set the PLL to stopped. */
    SYSTEM.PLLCR2.BYTE = 0x01;
#endif

    /* LOCO is saved for last since it is what is running by default out of reset. This means you do not want to turn
       it off until another clock has been enabled and is ready to use. */
#if (BSP_CFG_CLOCK_SOURCE == 0)
    /* LOCO is chosen. This is the default out of reset. */
    SYSTEM.LOCOCR.BYTE = 0x00;
#else
    /* LOCO is not chosen but it cannot be turned off yet since it is still being used. */
#endif

    /* Make sure a valid clock was chosen. */
#if (BSP_CFG_CLOCK_SOURCE > 4) || (BSP_CFG_CLOCK_SOURCE < 0)
    #error "ERROR - Valid clock source must be chosen in r_bsp_config.h using BSP_CFG_CLOCK_SOURCE macro."
#endif
}
