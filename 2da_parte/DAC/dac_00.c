#ifdef __USE_CMSIS
#include "lpc17xx.h"
#endif
#include <cr_section_macros.h>
#include <stdio.h>
#include "lpc17xx_pinsel.h"
#include "lpc17xx_dac.h"

void configPin();
void configDAC();
void delay();

int main(){
    uint32_t dac_values[11] = {0, 132, 223, 323, 423, 523, 623, 723, 823, 923, 1023};
    configPin();
    configDAC();

    while(1){
        for (uint8_t conta = 0; conta < 11; conta++)
        {
            DAC_UpdateValue(LPC_DAC, dac_values[conta]);
            delay();
        }
    }
}

void configPin(){
    PINSEL_CFG_Type pin_dac;
    pin_dac.Portnum = 0;
    pin_dac.Pinnum = 26;
    pin_dac.Pinmode = PINSEL_PINMODE_TRISTATE; //ninguno
    pin_dac.Funcnum = PINSEL_FUNC_2; //AOUT
    pin_dac.Portnum = PINSEL_PINMODE_NORMAL;
    PINSEL_ConfigPin(&pin_dac);
}

void ConfDAC(){
    DAC_Init(LPC_DAC); //por defecto max frec 1Mhz
}

void delay(){
    for (uint32 i = 0; i < 400000; i++);
}