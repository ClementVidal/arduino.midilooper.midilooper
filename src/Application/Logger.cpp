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
#include <Setup.h>

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
#if LOG_OVER_SERIAL
    Serial.begin( 9600 );
#endif
}

void CLogger::Log( const char* header,  const char* str, va_list args ) const
{
#if DEBUG
    char buffer[LOGGER_TMP_BUFFER_SIZE];

    vsnprintf( buffer, LOGGER_TMP_BUFFER_SIZE, str, args );

#if LOG_OVER_SERIAL
    Serial.print( "Info: " );
    Serial.println( buffer );
#endif

#endif
}

void CLogger::LogInfo( const char* str, ... ) const
{
#if DEBUG
    va_list args;

    va_start( args, str );
    Log( "Info: ", str, args );
    va_end( args ) ;
#endif
}

void CLogger::LogWarning( const char* str, ... ) const
{
#if DEBUG
    va_list args;

    va_start( args, str );
    Log( "Warning: ", str, args );
    va_end( args ) ;
#endif
}

void CLogger::LogError( const char* str, ... ) const
{
#if DEBUG
    va_list args;

    va_start( args, str );
    Log( "Error: ", str, args );
    va_end( args ) ;
#endif
}
