#include "typedefine.h"
#include <iodefine.h>

void tooggle_led4( void );
void delay_ms(uint32_t count);

void INT_Excep_ICU_IRQ8(void) __attribute__ ((interrupt));

/* ICU IRQ8*/
void INT_Excep_ICU_IRQ8(void)
{
	tooggle_led4();
}

void delay_ms(uint32_t count)
{
	int countms = 0;
	while(count--)
	{
		for(countms = 0; countms < 10; countms++);
	}
}

void tooggle_led4( void )
{
	PORTD.PODR.BIT.B5 = ~PORTD.PIDR.BIT.B5;
}

void configure_irq8(void)
{
	const uint16_t ulEnableRegisterWrite = 0xA50BU;
	const uint16_t ulDisableRegisterWrite = 0xA500U;

	/* Disable register write protection. */
	SYSTEM.PRCR.WORD = ulEnableRegisterWrite;
	{
		MPC.PWPR.BIT.B0WI = 0 ;     		/* Unlock protection register */
		MPC.PWPR.BIT.PFSWE = 1 ;    		/* Unlock MPC registers */

		/* Set P40, P41, and P44 for IRQx function */
		PORT4.PMR.BIT.B0  = 0;    /* All GPIO for now */
		MPC.P40PFS.BYTE = 0x40;    /* P40 is used as IRQ pin */
		/* Set IRQ type (falling edge) */
		ICU.IRQCR[8].BIT.IRQMD = 1;
		/* Set interrupt priority to 3 */
		IPR(ICU, IRQ8 ) = 0x05;
		/* Clear any pending interrupts */
		IR(ICU, IRQ8 ) = 0;
		/* Enable the interrupts */
		IEN(ICU, IRQ8 ) = 1;
	}
	/* Reneable register protection. */
	SYSTEM.PRCR.WORD = ulDisableRegisterWrite;

	ICU.IER[8].BYTE = 0xFFu;
}

int main(void)
{
	/* configure the LED4 for output */
	PORTD.PDR.BIT.B5 = 1;
	/* LED 5 output */
	PORTE.PDR.BIT.B3 = 1;

	/*
		Switch  Port    IRQ
	    ------  ----    ----
	    SW1     P4.0    IRQ8
	*/

	/* Make the pins inputs */
	PORT4.PDR.BIT.B0 = 0;
	configure_irq8();

    while(1)
    {
    	PORTE.PODR.BIT.B3 = ~PORTE.PIDR.BIT.B3;
    	delay_ms(1000);

    	//PORTD.PODR.BIT.B5 = 0;            /* turn on LED 4. */
		//delay_ms(1000);
		//PORTD.PODR.BIT.B5 = 1;            /* turn on LED 4. */
		//delay_ms(1000);
    }

    return 0;
}
