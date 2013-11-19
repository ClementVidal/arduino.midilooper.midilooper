#include <Arduino.h>

int main( void )
{
    
    init();
    Serial.begin( 9600 );

    pinMode( 13, OUTPUT );

    while(1) 
    {
        Serial.println("Hello world Bastard !!!!");
        digitalWrite( 13, HIGH );
        delay(1000);

        digitalWrite( 13, LOW);
        delay(1000);
    }
    return 0;
}
