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

#include <Application/Application.h>
#include <Arduino.h>

#include <MIDI.h>

using namespace NArduinoMIDILooper;

CApplication::CApplication()
{
}

CApplication::~CApplication()
{

}

void CApplication::Init()
{
    // Initialize Arduino Wire library...
    init();

    // Init MIDI library here 
    MIDI.begin();

    m_MemoryManager.Init();
    m_Logger.Init();
    m_Config.Init();
    m_UserInterface.Init();
    m_MIDIPlayer.Init();
    m_MIDIListener.Init();

    m_Session.Init();
}

void CApplication::Update()
{
    m_UserInterface.Update();
    m_MIDIListener.Update();
}
