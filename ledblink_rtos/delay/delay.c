#include "delay.h"

void delay_ms(uint32_t count)
{
	int countms = 0;
	while(count--)
	{
		for(countms = 0; countms < 10; countms++);
	}
}
