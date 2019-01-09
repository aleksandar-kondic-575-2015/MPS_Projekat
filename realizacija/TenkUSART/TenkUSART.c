#include "usart.h"

unsigned char odgovor = ~1;     // Pocetna vrednost - nijedan uslov nije ispunjen, ne moze da se gadja iz tenka
void main()
{
    UART1_Init_Advanced(56000, _UART_8_BIT_DATA, _UART_NOPARITY, _UART_ONE_STOPBIT, &_GPIO_MODULE_USART1_PA9_10);
    Delay_ms(100);
    
    GPIO_Digital_Input(&GPIOD_IDR, _GPIO_PINMASK_1 |             // Da li je zatvoren poklopac otvora vozac
                                   _GPIO_PINMASK_2 |             // Da li je zatvoren poklopac otvora komandira
                                   _GPIO_PINMASK_3 |             // Da li su zatvorena vrata nisandzije
                                   _GPIO_PINMASK_4 |             // Da li su zatvorena vrata punjaca
                                   _GPIO_PINMASK_5 |             // Da li je cev oslobodjena
                                   _GPIO_PINMASK_6 |             // Da li je punjac slobodan
                                   _GPIO_PINMASK_7);             // Da li ima dozvolu za gadjanje

    while (1)
    {
          if(UART1_Data_Ready() && UART1_Read() == 'a') {
                                odgovor = ~GPIOD_IDR & ~1;       // Invertuj sve bitove inputa i poslednji bit ocisti
                                if(odgovor == 0) {               // Ako su svi uslovi ispunjeni
                                           odgovor |= 1;         // Setuj bit indikatora da moze da se gadja iz tenka
                                }
                                UART1_Write(odgovor);
          }
    }
}