odgovor = ~GPIOD_IDR & ~1; // Invertuj sve bitove inputa i poslednji bit ocisti
if(odgovor == 0) { // Ako su svi uslovi ispunjeni
    odgovor |= 1; // Setuj bit indikatora da moze da se gadja iz tenka
}
UART1_Write(odgovor);
