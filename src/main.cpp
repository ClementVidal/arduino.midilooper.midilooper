#include <avr/io.h>
#include <util/delay.h>

#include <HardwareSerial.h> 
 
int main (void)
{
    
    Serial.begin( 9600 );

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
