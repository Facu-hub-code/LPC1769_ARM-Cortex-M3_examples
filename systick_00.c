/*Ejemplo basico de uso del systick*/

#include "LPC17xx.h"

void ledConfig();
void intConfig();
void systickConfig();

#define WAVEFORM 0xAA //(10101010)

int main(){
    ledConfig();
    intConfig();
    while (1){
        /* do nothing */
    }
    return 0;
}

void ledConfig(void){
	LPC_PINCON->PINSEL1 &= ~(3<<12); 	//P0.22 as GPIO
	LPC_GPIO0->FIODIR2 |= (1<<6); 		//P0.22 as output
}

void intConfig(){
    LPC_PINCON->PINSEL4 |= (1<<24); //P2.12 as EINT2
    LPC_SC->EXTMODE |= (1<<2); //P2.12 edge interrupt
    LPC_SC->EXTPOLAR &= ~(1<<2); //P2.12 falling edge
    LPC_SC-EXINT |= (1<<2); //P2.12 clear int flag
    NVIC_EnablerIRQ(EINT2_IRQn); //NVIC enable
    systickConfig();
}

void systickConfig(){
    SysTick->LOAD = ((SystemCoreClock/100)-1);
    SysTick->CTRL = (1) | (1<<1) | (1<<2);
    SysTick->VAL = 0;
    NVIC_SetPriority(SysTick_IRQn, 5);
}

void EINT2_IRQHandler(){
    static uint8_t state;
    if(state){
        LPC_GPIO0->FIOSET |= (1<<22); //Apago un led
        SysTick->CTRL &= ~(1<<1); //SysTick int disabled
    }else{
        SysTick->CTRL |= (1<<1); //SysTick int enabled
    }
}

void SysTickHandler(){
    static uint8_t clkDiv = 0;
    static uint8_t counter 0;
    if(clkDiv == 10){
        
    }
}