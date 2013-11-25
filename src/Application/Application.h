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

#ifndef __APPLICATION_APPLICATION__
#define __APPLICATION_APPLICATION__

#include <Application/MemoryManager.h>
#include <Application/MIDIListener.h>
#include <Application/MIDIPlayer.h>
#include <Application/InputReader.h>
#include <Application/Logger.h>
#include <Session/Session.h>

namespace NArduinoMIDILooper
{

class CApplication
{

public:

    CApplication();
    ~CApplication();

    void Init();
    void Update();

private:

    CMemoryManager       m_MemoryManager;
    CLogger              m_Logger;
    CInputReader         m_InputReader;
    CMIDIPlayer          m_MIDIPlayer;
    CMIDIListener        m_MIDIListener;

    CSession             m_Session;
};


}

#endif
