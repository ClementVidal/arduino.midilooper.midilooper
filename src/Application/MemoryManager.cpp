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

#include <Application/MemoryManager.h>

#include <SpiRAM.h>

using namespace NArduinoMIDILooper;

CMemoryManager::CMemoryManager() :
    m_FreeMemory( 0 )
{
    
}

CMemoryManager::~CMemoryManager()
{

}

void CMemoryManager::Init()
{

}

void* CMemoryManager::Reserve( int size )
{
#if DEBUG
    if( m_FreeMemory + size >= EXTERNAL_RAM_SIZE )
        Logger.LogError("Not enough external Ram");
#endif

    m_FreeMemory += size;
    
    return (void*) (m_FreeMemory - size);
}

bool CMemoryManager::Read( const void* address, void* data, int size )
{
    SpiRam.read_stream( (int) address, (char*)data, size );
    return true;
}

bool CMemoryManager::Write( const void* address, const void* data, int size )
{
    SpiRam.write_stream( (int) address, (char*)data, size );
    return true;
}
