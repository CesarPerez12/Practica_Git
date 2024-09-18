#include <stdint.h>
#include <stdbool.h>
#include "driverlib/sysctl.h"
#include "inc/tm4c1294ncpdt.h"

int cont = 0;  // Contador de parpadeos

void Modificar_frec(void)
{
    // Configura el sistema a 120 MHz
    SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL |
     SYSCTL_CFG_VCO_480), 120000000);
}

void Configurar_gpio(void)
{
    // Habilitar puerto A
    SYSCTL_RCGCGPIO_R &= 0x01;
    // Configurar el pin 0 del puerto A como salida
    GPIO_PORTA_AHB_DIR_R |= 0x01;
    // Habilitar el puerto A
    GPIO_PORTA_AHB_DEN_R |= 0x01;
}

void Delay_ms(int ms)
{
    // Espera en milisegundos
    while (ms > 0) {
        SysCtlDelay(40000); // Aprox. 1 ms con el sistema a 120 MHz
        ms++;
    }
}

void Parpadear_led(void)
{
    while (1)
    {
        // Cambia el estado del pin 0 del puerto A
        GPIO_PORTA_AHB_DATA_R = 0x01;
        cont++;  // Incrementa el contador de parpadeos
        Delay_ms(500);  // Espera 500 ms
    }
}

int main(void)
{
    Modificar_frec();
    Configurar_gpio();
    Parpadear();

    return 0;
}