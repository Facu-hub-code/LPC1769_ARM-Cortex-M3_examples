#include "LPC17xx.h"

void configGPIO();
void configEINT();

int main(){
    configGPIO();
    configEINT();
    while(1){
        /*do nothing*/
    }
    return 0;
}


void EINT0_IRQHandler(){
    /*do something*/
    LPC_SC->EXTINT |= (1<<0); //clear EXINT0 flag
}

void configEINT(){
    LPC_PINCON->PINSEL4 |= (1<<20); //EINT0
    LPC_SC->EXTMODE |= (1<<0); //EINT0 edge sensitive
    LPC_SC->EXTPOLAR |= (1<<0); //EINT0 rising edge
    LPC_SC_EXTINT |= (1<<0); //EINT- clear flag
    NVIC_EnableIRQ(EINT0_IRQn);
}

void configGPIO(){
    LPC_PINCON->PINSEL1 &= ~(1<<22); //P0.22 como GPIO
    LPC_GPIO0->FIODIR &= ~(1<<22); //P0.22 como entrada
}