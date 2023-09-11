/*
Enunciado:
Una famosa empresa de calzados a incorporado a sus zapatillas 
10 luces leds comandadas por un microcontrolador LPC1769
y ha pedido a su grupo de ingenieros que diseñen 2 secuencias de 
luces que cada cierto tiempo se vayan intercalando 
(secuencia A - secuencia B- secuencia A- ... ). 
 
Como todavía no se ha definido la frecuencia a la cual va a 
funcionar el CPU del microcontrolador, las funciones de retardos que
se incorporen deben tener como parametros de entrada variables que
permitan modificar el tiempo de retardo que se vaya a
utilizar finalmente. Se pide escribir el código que resuelva este
pedido, considerando que los leds se encuentran conectados en
los puertos P0,0 al P0.9.
*/

/*
Resumen:
Tenemos que configurar los pines 0-9 del puerto 0 como salida GPIO
Tenemos que escribir dos secuencias distintas de luces.
*/

#include "LPC17xx.h"

#define LED_COUNT 10

void configGPIO();
void delay(uint32_t time);
void secuencia1();
void secuencia2();

int main(){
    configGPIO();
    while (1)
    {
        secuencia1();
        secuencia2();
    }
    return 0;   
}

void configGPIO(void){
    LPC_PINCON->PINSEL0 &= ~(0xFFFFF); //PORT0 pines[9:0] como GPIO
    LPC_GPIO0->FIODIR |= (0x03FF); //Pines [9:0] del PORT0 como salida 
}

void delay(uint32_t time){
    while(count --);
}

void secuencia1() {
    for (int i = 0; i < LED_COUNT; i++) {
        // Enciende el LED actual
        LPC_GPIO0->FIOSET |= (1 << i);

        // Espera un tiempo
        delay(500);

        // Apaga el LED actual
        LPC_GPIO0->FIOCLR |= (1 << i);
    }
}

void secuencia2() {
    for (int i = 0; i < LED_COUNT / 2; i++) {
        // Enciende dos LEDs simultáneamente
        LPC_GPIO0->FIOSET = (1 << i) | (1 << (LED_COUNT - i - 1));

        // Espera un tiempo
        delay(500);

        // Apaga los LEDs
        LPC_GPIO0->FIOCLR = (1 << i) | (1 << (LED_COUNT - i - 1));
    }
}