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

#ifndef __APPLICATION_LOGGER__
#define __APPLICATION_LOGGER__

#include <stdio.h>

namespace NArduinoMIDILooper
{

class CLogger
{

public:

    CLogger();
    ~CLogger();

    void Init();

    void LogInfo( const char* str, ... ) const;
    void LogWarning( const char* str, ... ) const;
    void LogError( const char* str, ... ) const;

private:

    void Log( const char* header,  const char* str, va_list args ) const;

};

}

#endif
