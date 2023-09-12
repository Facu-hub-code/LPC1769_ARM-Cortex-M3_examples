/*
Algoritmo de antirrebote de un pulsador: Escribir un programa en C que ante la 
interrupción por flanco de subida del pin P0.1, configurado como entrada digital con 
pull-down interno, se incremente un contador de un dígito, se deshabilite esta 
interrupción y se permita la interrupción por systick cada 20 milisegundos. 
En cada interrupción del systick se testeará una vez el pin P0.1. 
Solo para el caso de haber testeado 3 estados altos seguidos se sacará por los pines 
del puerto P2.0 al P2.7 el equivalente en ascii del valor del contador, se desactivará 
las interrupción por systick y se habilitará nuevamente la interrupción por P0.1. 
Por especificación de diseño se pide que los pines del puerto 2 que no sean utilizados 
deben estar enmascarados por hardware. Considerar que el CPU se encuentra funcionando 
con el oscilador interno RC (4Mhz). 
*/