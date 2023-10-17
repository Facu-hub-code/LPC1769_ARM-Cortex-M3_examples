/*
Entre los pines P2.0 a P2.7 se encuentra conectado un display de 7 segmentos. 
Utilizando la variable numDisplay [10] ={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67} 
que codifica los números del 0 a 9 para ser mostrados en el display, realizar un programa 
que muestre indefinidamente la cuenta de 0 a 9 en dicho display.
*/

#include "LPC17xx.h"

void configGPIO();
void showDisplay(uint8_t num_to_show);
void delay(uint32_t time_count);

uint8_t numDisplay [10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67};

int main(){
    configGPIO();
    while(1){
        for (int i = 0; i < numDisplay.lenght(); i++)
        {
            showDisplay(i);
            delay(50000);
        }         
    }
}

void configGPIO(){
    LPC_PINCON->PINSEL4 &= ~(0xFFFF);//Pines 0 al 7 del PORT2 como GPIO.
    LPC_GPIO2->FIODIR |= (0xFF); //Pines del 0 al 7 del PORT2 como salida
}

void showDisplay(uint8_t num_to_show){
    LPC_GPIO2->FIOSET |= (numDisplay[num_to_show]);
}

void delay(uint32_t time_count){
    while(time_count --);
}