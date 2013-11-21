/*

Copyright 2013 Clement Vidal - clementvidalperso@gmail.com


This file is part of ArduinoMIDILooper.

ArduinoMIDILooper is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

ArduinoMIDILooper is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with ArduinoMIDILooper.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <Application/Logger.h>

#include <Arduino.h>

#define LOGGER_TMP_BUFFER_SIZE 64

using namespace NArduinoMIDILooper;

CLogger::CLogger()
{

}

CLogger::~CLogger()
{

}

void CLogger::Init()
{
    Serial.begin( 9600 );
}

void CLogger::Log( const char* header,  const char* str, va_list args ) const
{
    char buffer[LOGGER_TMP_BUFFER_SIZE];

    vsnprintf( buffer, LOGGER_TMP_BUFFER_SIZE, str, args );

    Serial.print( "Info: " );
    Serial.println( buffer );
}

void CLogger::LogInfo( const char* str, ... ) const
{
    va_list args;

    va_start( args, str );
    Log( "Info: ", str, args );
    va_end( args ) ;
}

void CLogger::LogWarning( const char* str, ... ) const
{
    va_list args;

    va_start( args, str );
    Log( "Warning: ", str, args );
    va_end( args ) ;
}

void CLogger::LogError( const char* str, ... ) const
{
    va_list args;

    va_start( args, str );
    Log( "Error: ", str, args );
    va_end( args ) ;
}
