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

#ifndef __APPLICATION_MEMORYMANAGER__
#define __APPLICATION_MEMORYMANAGER__

#include <Application/Singleton.h>

#define MemoryManager (CMemoryManager::GetInstance())

namespace NArduinoMIDILooper
{

class CMemoryManager : public CSingleton<CMemoryManager>
{

public:

    CMemoryManager();
    ~CMemoryManager();

    void Init();

    int  Reserve( int size );
    bool Read( int address, char* data, int size );
    bool Write( int address, char* data, int size );

private:

    int m_FreeMemory;

};

}

#endif
