#include "MKL25Z4.h"

uint8_t ADC_Read8b(uint16_t channel); // Citirea unui octet de pe canalul interfetei ADC dat ca parametru
void initADC(void); // Initilizarea modulului ADC
int calibrareADC0(void); //Calibrarea modului ADC 