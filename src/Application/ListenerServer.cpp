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

#include <Application/ListenerServer.h>

#include <MIDI.h>

using namespace NArduinoMIDILooper;

static void NoteOnCB(byte channel, byte note, byte velocity);
static void NoteOffCB(byte channel, byte note, byte velocity);
static void PitchBendCB(byte channel, int pitchBend);
static void ChannelPressureCB(byte channel, byte pressure);
static void ControlChangeCB(byte channel, byte number, byte value);
static void StartCB();
static void StopCB();
static void ClockCB();

CListenerServer::CListenerServer()
{

}

CListenerServer::~CListenerServer()
{

}

void CListenerServer::Init()
{
    MIDI.setHandleNoteOn( NoteOnCB );
    MIDI.setHandleNoteOff( NoteOffCB );
    MIDI.setHandlePitchBend( PitchBendCB );
    MIDI.setHandleAfterTouchChannel( ChannelPressureCB );
    MIDI.setHandleStart( StartCB );
    MIDI.setHandleStop( StopCB );
    MIDI.setHandleClock( ClockCB );
    MIDI.setHandleControlChange( ControlChangeCB );
}

void NoteOnCB(byte channel, byte note, byte velocity)
{
}

void NoteOffCB(byte channel, byte note, byte velocity)
{
}

void PitchBendCB(byte channel, int pitchBend)
{
}

void ChannelPressureCB(byte channel, byte pressure)
{
}

void ControlChangeCB(byte channel, byte number, byte value)
{
}

void StartCB()
{
}

void StopCB()
{
}

void ClockCB()
{
}
