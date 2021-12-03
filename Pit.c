#include "Pit.h"


void initPIT() 
{
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;
	
	PIT_MCR = 0x00;
	
	//PIT_LDVAL1 = 0x017D783F; // setup timer la 25.000.000 de cicluri (1 sec)
	//PIT_LDVAL1 = 0x0003E7FF; //setup timer la 256.000 de cicluri ( ~ 10 milisec)
	PIT_LDVAL1 = 0X000063FF; //setup timer la 25.600 de cicluri (~ 1 milisec)
	PIT_TCTRL1 = PIT_TCTRL_TIE_MASK;
	PIT_TCTRL1 |= PIT_TCTRL_TEN_MASK;
	
	NVIC_ClearPendingIRQ(PIT_IRQn);
	NVIC_SetPriority(PIT_IRQn,128);
	NVIC_EnableIRQ(PIT_IRQn);
}