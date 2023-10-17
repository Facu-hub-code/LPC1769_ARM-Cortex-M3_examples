#ifdef __USE_CMSIS
#include "lpc17xx.h"
#endif
#include <cr_section_macros>
#include <stdio.h>
#include "lpc17xx_pinsel.h"
#include "lpc17xx_exti.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_timer.h"

#define PIN_4 ((uint32_t))

void configGPIO();
void configTimer();
void TIMER0_IRQHandler();
void EINT0_IRQHandler();

int main(){
    uint32_t clk = SystemCoreClock;
    SystemInit();
    configGPIO();
    configTimer();
    
    while (1){}
    
    return 0;
}

/*Configura el pin P2.4 como una salida GPIO*/
void configGPIO(){
    PINSEL_CFG_Type pin;
    pin.Portnum = 2;
    pin.Pinnum = 4;
    pin.Pinmode = 0;
    pin.Funcmode = 0;
    pin.OpenDrain = 0;
    PINSEL_ConfigPin(&pin);
    GPIO_SetDir(2, 4, 1);
}

/*El TMR0 esta configurado para togglear el pin P1.28*/
void configTIMER0(){
    PINSEL_CFG_Type pin; /*P1.28 EXTMATCH*/
    TIM_TIMERCFG_Type tmr; //prescaler
    TIM_MATCHCFG_Type match; //match

    pin.Portnum = 1;
    pin.Pinnum = 28;
    pin.Pinmode = 0;
    pin.Funcmode = 3; //Funcion EXTMATCH0.0
    pin.OpenDrain = 0;
    
    tmr.PrescaleOption = TIM_PRESCALE_TICKVAL;
    tmr.PrescaleValue = 1;

    match.MatchChanel = 0;
    match.IntOnMatch = ENABLE;
    match.ResetOnMatch = ENABLE;
    match.StopOnMatch = DISABLE;
    match.ExtMatchOutputType = TIM_EXTMATCH_TOGGLE;
    match.MatchValue = 12499999;

    PINSEL_ConfigPin(&pin);
    TIM_Init(LPC_TIM0, &tmr);
    TIM_ConfigMatch(LPC_TIM0, &match);
    Tim_Cmd(LPC_TIM0, ENABLE);
    NVIC_EnableIRQ(TIMER0_IRQn);
}

void TIMER_IRQHandler(){
    if(TIM_GetIntStatus(LPC_TIM0, 0)){
        if(GPIO_ReadValue(2) & PIN_4){
            GPIO_ClearValue(2, PIN_4);
        }else{
            GPIO_SetValue(2, PIN_4);
        }
        TIM_ClearIntPending(LPC_TIM0, 0);
    }
}