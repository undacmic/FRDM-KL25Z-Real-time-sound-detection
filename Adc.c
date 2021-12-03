#include "Adc.h"

void initADC() 
{
	SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;
	
	ADC0->CFG1 |= 	(ADC_CFG1_MODE(0) | ADC_CFG1_ADIV(3));
	
	ADC0_SC1A = ADC_SC1_ADCH(31); //dezactivare prin setarea tuturor bitilor
	
}

uint8_t ADC_Read8b(uint16_t channel)
{
	ADC0_SC1A = channel & ADC_SC1_ADCH_MASK; //Activez monitorizarea pe canalul dorit (determinat de pinul de input)
	
	while(ADC0_SC2 & ADC_SC2_ADACT_MASK); //Verific daca o conversie este in desfasurare
	while(!(ADC0_SC1A & ADC_SC1_COCO_MASK)); //Verific daca conversia s-a realizat
	return ADC0_RA;
	
	
}