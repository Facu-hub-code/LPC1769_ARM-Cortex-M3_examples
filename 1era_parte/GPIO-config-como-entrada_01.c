/*
Escribir un programa en C que permita realizar un promedio movil con los últimos 8 
datos ingresados por el puerto 1. Considerar que cada dato es un entero signado y está 
formado por los 16 bits menos significativos de dicho puerto. 
El resultado, también de 16 bits, debe ser sacado por los pines P0.0 al P0.11 y P0.15 
al P0.18. 

Recordar que en un promedio movil primero se descarta el dato mas viejo de los 8 datos
guardados, se ingresa un nuevo dato proveniente del puerto y se realiza la nueva 
operación de promedio con esos 8 datos disponibles, así sucesivamente.

Considerar el uso de un retardo antes de tomar una nueva muestra por el puerto. 
*/

#include "LPC17xx.h"

//Dato ingresante = 16 bits menos sig del PORT1
uint16_t input, output; //Dato de entrada al arreglo y promedio resultante.
uint16_t data[8] = {0,0,0,0,0,0,0,0}; //Arreglo de los ultimos 8 datos.

void configGPIO();
void tomarValorPort1(void);
uint16_t calcularPromedio();
void delay(uint32_t time_count);
void reordenarArreglo();
void mostrarResultado();

int main(){
    configGPIO();
    while(1){
        tomarValorPort1();
        calcularPromedio();
        reordenarArreglo();
        mostrarResultado();
        delay(5000);
    }
    return 0;
}

/*
Al puerto le muestro primero los primeros bits y en otra instruccion los siguientes.
*/
void mostrarResultado(){   

}

void tomarValorPort1(){
    input = LPC_GPIO1->FIOPIN;
}

/*
Configurar:
    PORT1 pines [15:0] como entrada GPIO y
    PORT0 pines [11:0],[18:15] como salida GPIO.  
 */
void configGPIO(void){
    LPC_PINCON->PINSEL2 &= ~(0xFFFFF); //Set PORT1 como GPIO
    LPC_PINCCON->PINSEL0 &= ~(0xFFFFFF); //Set PORT0 como GPIO
    LPC_GPIO1->FIODIR &= ~(0xFFFFF); //Set PORT1 como entrada
    LPC_GPIO0->FIODIR |= (0xFFFFFF); //Set PORT0 como salida
}

void delay(uint32_t time_count){
    while(time_count --);
}

void calcularPromedio(){
    uint16_t aux = 0;
    for (int i = 0; i < data.lenght; i++)
    {
        aux += data[i];  //Sumo todos los valores del arreglo
    }
    output = aux/data.lenght; //Calculo el promedio y se lo cargo a la variable global
}

/*
    Al ultimo valor data[8] le escribo el ante ultimo data[8-1]
    Luego segun como incremente i voy corriendo los valores a la derecha.
*/
void reordenarArreglo(){
    for (int i = 0; i < data.lenght; i++)
    {
        data[data.lenght - i] = data[data.lenght - (i+1)];
    }
}