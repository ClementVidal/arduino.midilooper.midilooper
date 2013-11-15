#include <avr/io.h>
#include <util/delay.h>

#include <HardwareSerial.h> 
 
int main (void)
{
    
    while(1) 
    {
        Serial.println("Hello world!");

        PORTB |= _BV(PORTB5);
        _delay_ms(1000);
        PORTB &= ~_BV(PORTB5);
        _delay_ms(1000);
    }
    return 0;
}
