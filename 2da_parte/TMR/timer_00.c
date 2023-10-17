#ifdef __USE_CMSIS
#include "lpc_17xx.h"
#endif

#include "lpc17xx_pinsel.h"
#include "lpc17xx_exti.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_timer.h"

#define PIN_4 ((uint32_t) (1<<4))

void configGPIO(); //configura el P2.4 como salida
void configTIMER0(); //configura el timer 0
void configEINT0();
void TIMER0_IRQHandler();
void EINT0_IRQHandler();

uint32_t pclktimer0 = 0;

int main(){
    uint32_t verClk = SystemCoreClock;
    SystemInit();
    configGPIO();
    configEINT0();
    configTIMER0();

    while(1){}

    return 0;
}

void configGPIO(){
    PINSEL_CFG_Type p;
    p.Portnum = 2; //puerto 2
    p.Pinnum = 4; //pin 4
    p.Pinmode = 0; //Pull up (no importa porque va ser una salida)
    p.Funcmode = 0; //Funcion GPIO
    p.OpenDrain = 0; //Sin open drain
    PINSEL_ConfigPin(&p);
    GPIO_SetDir(2, 4, 1); //P2.4 como salida
}

configEINT0(){
    /*Configuro P2.10 como EINT*/
    PINSEL_CFG_Type p;
    p.Portnum = 2;
    p.Pinnum = 10;
    p.Pinmode = 0; //pull up (no importa pq es salida)
    p.Funcmode = 1; //Funcion EINT0
    p.OpenDrain = 0; //Sin open drain
    PINSEL_ConfigPin(&p);

    EXTI_SetMode(0, 1); // EINT0 por flanco
    EXTI_SetPolarity(0, 0); //EINT0 polaridad flanco de bajada
    NVIC_SetPriority(EINT0_IRQn, 30); //asigna la prioridad de EINT0
}

configTIMER0(){
    PINSEL_CFG_Type pin; //P1.28 EXTMATCH 0.0
    TIM_TIMERCFG_Type tmr; //configuracion del timer
    TIM_MATCHCFG_Type match;

    /*Configuro el puerto que va ser afectado por el TMR*/
    port.Portnnum = 1;
    port.Pinnum = 28;
    port.Pinmode = 0; //pull up (no importa porque va a ser salida)
    port.Funcmode = 3; //EXTMATCH0.0
    port.OpenDrain = 0; //sin opendrain

    /*Configuracion del prescaler*/
    tmr.tmrescaleOption = TIM_PRESCALE_TICKVAL; //Valor absoluto
    //pr.PrescaleOption = TIM_PRESCALE_USVAL;
    tmr.PrescaleValue = 1; //Valor del prescaler
    //pr.PrescaleValue = 500;

    /*Configuracion del MATCH*/
    match.MatchCHanel = 0; //Cual de los 4 registros match usar
    match.IntOnMatch = ENABLE; //Interrumpe
    match.ResetOnMatch = ENABLE; //Resetea
    match.StopOnMatch = DISABLE; //No se detiene
    match.ExtMatchOutputType = TIM_EXTMATCH_TOGGLE;
    match.matchValue = 12499999;
    //match.matchValue = 1000;
    
    PINSEL_ConfigPin(&pin);
    TIM_Init(LPC_TIM0, TIM_TIMER_MODE, &tmr);
    TIM_ConfigMatch(LPC_TIM0, &match);
    TIM_Cmd(LPC_TIM0, ENABLE); //Habilita el timer counter y prescale counter
    NVIC_EnableIRQ(TIEMR0_IRQn);
}