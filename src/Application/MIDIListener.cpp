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

#include <Application/MIDIListener.h>
#include <Session/Session.h>
#include <Session/Event.h>

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

CMIDIListener::CMIDIListener()
{

}

CMIDIListener::~CMIDIListener()
{

}

void CMIDIListener::Init()
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
    CEvent e;
    e.Type = CEvent::nType_NoteOn;
    e.Data[0] = note;
    e.Data[1] = velocity;
    e.Data[2] = 0;
    Session.OnEvent( e );
}

void NoteOffCB(byte channel, byte note, byte velocity)
{
    CEvent e;
    e.Type = CEvent::nType_NoteOff;
    e.Data[0] = note;
    e.Data[1] = velocity;
    e.Data[2] = 0;
    Session.OnEvent( e );
}

void PitchBendCB(byte channel, int pitchBend)
{
    CEvent e;
    e.Type = CEvent::nType_PitchBend;
    e.Data[0] = 0;
    e.Data[1] = 0;
    e.Data[2] = 0;
    Session.OnEvent( e );
}

void ChannelPressureCB(byte channel, byte pressure)
{
    CEvent e;
    e.Type = CEvent::nType_ChannelPressure;
    e.Data[0] = pressure;
    e.Data[1] = 0;
    e.Data[2] = 0;
    Session.OnEvent( e );
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
