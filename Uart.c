#include "Uart.h"

uint32_t osr = 15;
uint16_t sbr;
uint8_t temp;

void UART0_Transmit(uint8_t data)
{
	
	while(!(UART0->S1 & UART0_S1_TDRE_MASK));
				UART0->D = data;
	
}

uint8_t UART0_receive(void)
{
	
	while(!(UART0->S1 & UART0_S1_RDRF_MASK));
				return UART0->D;
	
}

void initUART0(uint32_t baud_rate)
{
	
	//Initializarea ceasului pentru UART0 si pentru PORTA
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
	UART0->C2 &= ~((UART0_C2_RE_MASK) | (UART0_C2_TE_MASK)); 
	
	
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(01);
	SIM->SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;
	
	PORTA->PCR[1] &= ~PORT_PCR_MUX_MASK;
	PORTA->PCR[1] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2); // UART0_RX -> PTA1
	PORTA->PCR[2] &= ~PORT_PCR_MUX_MASK;
	PORTA->PCR[2] |= PORT_PCR_ISF_MASK | PORT_PCR_MUX(2); // UART0_TX -> PTA2
	
	
	sbr = (uint16_t)((DEFAULT_SYSTEM_CLOCK)/(baud_rate * (osr+1)));
	temp = UART0->BDH & ~(UART0_BDH_SBR(0x1F));
	UART0->BDH = temp | UART0_BDH_SBR(((sbr & 0x1F00)>> 8));
	UART0->BDL = (uint8_t)(sbr & UART_BDL_SBR_MASK);
	UART0->C4 |= UART0_C4_OSR(osr);
	
	UART0->C1 = 0;
	UART0->C3 = 0;
	UART0->MA1 = 0;
	UART0->MA2 = 0;
	UART0->S1 = 0x00;
	UART0->S2 = 0x00;
	
	UART0->C2 |= ((UART_C2_RE_MASK) | (UART_C2_TE_MASK));
	
	
}
