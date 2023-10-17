/*
Realizar un programa que configure el puerto P0.0 y P2.0 para que provoquen una 
interrupción por flanco de subida. 
Si la interrupción es por P0.0 guardar el valor binario 100111 en la variable 
"auxiliar", si es por P2.0 guardar el valor binario 111001011010110.
*/

#include "LPC17xx.h"

void configGPIO(void);
void configGPIOInterrupt(void)

uint16_t auxiliar;

int main(void){
    configGPIO();
    configGPIOInterrupt();
    while(1){
        /*do nothing*/
    }
    return 0;
}

void EINT3_IRQHandler(){
    if(LPC_GPIOINT->IO2IntStatR & (0x1)) {   
        auxiliar = b'100111';
    }else{
        auxiliar = b'111001011010110';
    }
}

void configGPIO(){
    LPC_PINCON->PINSEL4 &= ~(0x3); //P2.0 como GPIO
    LPC_PINCON->PINSEL0 &= ~(0x3); //P0.0 como GPIO
    LPC_GPIO2->FIODIR &= ~(0x1); //P2.0 como entrada
    LPC_GPIO0->FIODIR &= ~(0x1); //P0.0 como entrada 
}

void configGPIOInterrupt(void){
    LPC_GPIOINT->IO2IntEnR |= (0x1); //P2.0 interrumpe por flanco de subida
    LPC_GPIOINT->IO0IntEnR |= (0x1); //P0.0 interrumpe por flanco de subida
    NVIC_EnableIRQ(EINT3_IRQn); //Habilito la interrupcion por GPIO
}

