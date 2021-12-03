#include "MKL25Z4.h"

void UART0_Transmit(uint8_t data); // Functie folostia pentru a trimite un octet catre interfata UART
uint8_t UART0_receive(void); // Functie ce returneaza un octet de pe interfata UART, atunci cand acesta exista un buffer
void initUART0(uint32_t baud_rate); // Initializare a modulului UART pentru trasmiterea datelor, ce primeste ca parametru baud rate-ul dorit
