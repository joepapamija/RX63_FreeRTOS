#include <iodefine.h>
#include "delay.h"

#include "freeRTOS.h"
#include "task.h"

void ledblinkTask(void *params)
{
	PORTD.PDR.BIT.B5 = 1;
	for(;;)
	{
		PORTD.PODR.BIT.B5 = ~PORTD.PIDR.BIT.B5;
		vTaskDelay(1000/portTICK_PERIOD_MS);
	}
}

int main(void)
{
	xTaskCreate(ledblinkTask, "LED", configMINIMAL_STACK_SIZE, ( void * ) NULL, tskIDLE_PRIORITY+1, NULL );
	vTaskStartScheduler();

	for(;;);

    return 0;
}

void vApplicationSetupTimerInterrupt( void )
{
	/* protect off */
	SYSTEM.PRCR.WORD = 0xA502;
	/* Enable compare match timer 0. */
	MSTP( CMT0 ) = 0;
	/* Interrupt on compare match. */
	CMT0.CMCR.BIT.CMIE = 1;
	/* Set the compare match value. */
	CMT0.CMCOR = ( unsigned short ) ( ( ( configPERIPHERAL_CLOCK_HZ / configTICK_RATE_HZ ) -1 ) / 8 );
	/* Divide the PCLK by 8. */
	CMT0.CMCR.BIT.CKS = 0;
	/* Enable the interrupt... */
	_IEN( _CMT0_CMI0 ) = 1;
	/* ...and set its priority to the application defined kernel priority. */
	_IPR( _CMT0_CMI0 ) = configKERNEL_INTERRUPT_PRIORITY;
	/* Start the timer. */
	CMT.CMSTR0.BIT.STR0 = 1;
}
/*-----------------------------------------------------------*/

/* This function is explained by the comments above its prototype at the top
of this file. */
void vApplicationMallocFailedHook( void )
{
	for( ;; );
}
/*-----------------------------------------------------------*/

/* This function is explained by the comments above its prototype at the top
of this file. */
void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
	for( ;; );
}
/*-----------------------------------------------------------*/

/* This function is explained by the comments above its prototype at the top
of this file. */
void vApplicationIdleHook( void )
{
	/* Just to prevent the variable getting optimised away. */
	//( void ) ulHighFrequencyTickCount;
}
