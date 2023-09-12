/*
Realizar un programa que configure el puerto P2.0 y P2.1 para que provoquen una 
interrupción por flanco de subida para el primer pin y por flanco de bajada para el 
segundo. 
Cuando la interrupción sea por P2.0 se enviará por el pin P0.0 la secuencia de 
bits 010011010. Si la interrupción es por P2.1 se enviará por el pin P0.1 la 
secuencia 011100110. 
Las secuencias se envían únicamente cuando se produce una interrupción, en caso 
contrario la salida de los pines tienen valores 1 lógicos. 
¿que prioridad tienen configuradas por defecto estas interrupciones? 
*/

#include "LPC17xx.h"

void configGPIO(void);
void configGPIOInterrupt(void)

int main(void){
    configGPIO();
    configGPIOInterrupt();
    while(1){
        /*do nothing*/
    }
    return 0;
}

void EINT3_IRQHandler(void){
    //debounce treating
    if(LPC_GPIOINT->IO2IntStatR ) //TODO: Como revisar que bit es
    {   
        LPC_GPIO2->FIOSET |= b'010011010';
    }
    else
    {
        // mando el otro xdxd

    }
}

void configGPIO(){
    LPC_PINCON->PINSEL4 &= ~(0xF); //P2.0 y P2.1 como GPIO
    LPC_PINCON->PINSEL0 &= ~(0xF); //P0.0 y P0.1 como GPIO
    LPC_GPIO2->FIODIR &= ~(0x3); //P2.0 y P2.1 como entrada
    LPC_GPIO0->FIODIR |= (0x3); //P0.0 y P0.1 como salida
    LPC_PINCON->PINMODE0 &= ~(0x3); //P0.0 y P0.1 como pull-up 
}

void configGPIOInterrupt(void){
    LPC_GPIOINT->IO2IntEnR |= (0x1); //P2.0 interrumpe por flanco de subida
    LPC_GPIOINT->IO2IntEnF |= (0x2); //P2.1 interrumpe por flanco de bajada
}

