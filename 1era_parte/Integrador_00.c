#include "LPC17xx.h"

void configGPIO(void);
void configEXTI(void);
void configSysTick(void);

static final int signal[19] = {1,0,1,0,1,0,1,0,0,0,0,1,0,1,0,1,0,1,0};
static int count = 0;

int main(){
    configEXTI();
    configGPIO();
    configSysTick();
    while (1){/* do nothing */}
    return 0;
}

/*
P2.4 GPIO input int rising
P2.5 GPIO output
*/
void configGPIO(){
    LPC_PINCON->PINSEL
}
void configEXTI();
void configSysTick();

void EXTINT3_IRQHandler(){

}

void SysTick_IRQHandler(){

}