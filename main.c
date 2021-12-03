#include "MKL25Z4.h"
#include "Uart.h"
#include "Adc.h"
#include "Pit.h"

uint32_t dataOverInterval;

void PIT_IRQHandler(void)
{	
	/*
	* Vom considera valoarea maxima obtinuta per interval de 10ms ca fiind egala cu 50000
	* Astfel, vom aplica o regula de 3 simpla pentru a transpune aceasta valoare in intervalul [0,255]
	* pentru a putea trasnmite prin UART pe portul serial si prelua mai apoi de MATLAB
	*/
	
	PIT_TFLG1 = 0x01; 
	uint32_t goodValue = (dataOverInterval * 255) / 50000;
	if(goodValue > 255)
	{
			goodValue = 255;
	}
	UART0_Transmit((uint8_t)goodValue);
	dataOverInterval = 0;
	
	//if(goodValue == 0)
	//{
		//UART0_Transmit(0x30);
	//}
	//else
	//{
		//Convert_8b_to_Decimal_String(goodValue);
		//for(current_index=size;current_index<3;current_index++)
		//{
				//UART0_Transmit(mystring[current_index]);
				//mystring[current_index]= 0x30;
		//}
	//}
	
	//UART0_Transmit('\r');
	//UART0_Transmit('\n');
	//size=3;
	//dataOverInterval = 0;
}
char mystring[]="000";
int current_index = 0;
int size = 6;
void Convert_8b_to_Decimal_String(uint32_t data)
{
	while(data)
	{
		uint8_t lastDigit = data%10;
		if(lastDigit)
		{
			size--;
			mystring[size] += lastDigit;
		}
		data /= 10;
	}
}

int main()
{

	initUART0(115200);
	initADC();
	initPIT();
	
	uint8_t data;
	while(1) {
		data = ADC_Read8b(8);
		dataOverInterval += data;
		//UART0_Transmit(result);
		//}

		//UART0_Transmit('\r');
		//UART0_Transmit('\n');
		//Delay_ms(10);
	}
	
	
	return 0;
	
}