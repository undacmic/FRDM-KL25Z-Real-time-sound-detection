#include "Adc.h"

void initADC() 
{
	SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;
	
	calibrareADC0();
	
	ADC0->CFG1 |= 	(ADC_CFG1_MODE(0) | ADC_CFG1_ADIV(3));
	
	ADC0_SC1A = ADC_SC1_ADCH(31); //dezactivare prin setarea tuturor bitilor
	
}
int calibrareADC0() 
{
      uint16_t castigCalibrare;
			ADC0_SC2 |= ADC_SC2_ADTRG(0);
			ADC0_SC3 |= (1<<6);//setam bitul 7 pentru a incepe o calibrare automata daca SC2[ADTRG] este 0.
      //calcularea partii plus a calibrarii
      castigCalibrare = 0x00;
      castigCalibrare = ADC0_CLP0;
      castigCalibrare += ADC0_CLP1;
      castigCalibrare += ADC0_CLP2;
      castigCalibrare += ADC0_CLP3;
      castigCalibrare += ADC0_CLP4;
      castigCalibrare += ADC0_CLPS;
      castigCalibrare = castigCalibrare / 2;
      //seteaza MSB
      castigCalibrare |= 0x8000; 
      //castigul partii plus
      ADC0_PG = ADC_PG_PG(castigCalibrare);
      
      //calcularea partii minus a calibrarii
      castigCalibrare = 0x00;
      castigCalibrare = ADC0_CLM0;
      castigCalibrare += ADC0_CLM1;
      castigCalibrare += ADC0_CLM2;
      castigCalibrare += ADC0_CLM3;
      castigCalibrare += ADC0_CLM4;
      castigCalibrare += ADC0_CLMS;
      castigCalibrare = castigCalibrare / 2;
      castigCalibrare |= 0x8000; 
      ADC0_MG = ADC_MG_MG(castigCalibrare);
      
			ADC0_SC3 &= ~(ADC_SC3_CAL_MASK);
      return (0);
}


uint8_t ADC_Read8b(uint16_t channel)
{
	ADC0_SC1A = channel & ADC_SC1_ADCH_MASK; //Activez monitorizarea pe canalul dorit (determinat de pinul de input)
	
	while(ADC0_SC2 & ADC_SC2_ADACT_MASK); //Verific daca o conversie este in desfasurare
	while(!(ADC0_SC1A & ADC_SC1_COCO_MASK)); //Verific daca conversia s-a realizat
	return ADC0_RA;
	
	
}