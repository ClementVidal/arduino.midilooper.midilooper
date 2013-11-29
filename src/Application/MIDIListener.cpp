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
#include <Application/Config.h>
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
static ClockCount DeltaClockCount = 0;

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

void CMIDIListener::Update()
{
    MIDI.read( Config.MIDIInputChannel );
}

void NoteOnCB(byte channel, byte note, byte velocity)
{
    CEvent e;
    e.Type = CEvent::nType_NoteOn;
    e.ByteData[0] = note;
    e.ByteData[1] = velocity;
    e.DeltaClockCount = DeltaClockCount;

    Session.OnEvent( e );

    DeltaClockCount = 0;
}

void NoteOffCB(byte channel, byte note, byte velocity)
{
    CEvent e;
    e.Type = CEvent::nType_NoteOff;
    e.ByteData[0] = note;
    e.ByteData[1] = velocity;
    e.DeltaClockCount = DeltaClockCount;

    Session.OnEvent( e );

    DeltaClockCount = 0;
}

void PitchBendCB(byte channel, int pitchBend)
{
    CEvent e;
    e.Type = CEvent::nType_PitchBend;
    e.IntData = 0;
    e.DeltaClockCount = DeltaClockCount;

    Session.OnEvent( e );

    DeltaClockCount = 0;
}

void ChannelPressureCB(byte channel, byte pressure)
{
    CEvent e;
    e.Type = CEvent::nType_ChannelPressure;
    e.ByteData[0] = pressure;
    e.ByteData[1] = 0;
    e.DeltaClockCount = DeltaClockCount;

    Session.OnEvent( e );

    DeltaClockCount = 0;
}

void ControlChangeCB(byte channel, byte number, byte value)
{
    if( number == Config.StartStopRecordCC )
    {
        if( Session.GetStatus() == CSession::nStatus_Idle || 
            Session.GetStatus() == CSession::nStatus_Playing )
        {
            Session.StartRecord();
        }
        else if( Session.GetStatus() == CSession::nStatus_Recording )
        {
            Session.Stop();
        }
    }
    else if( number == Config.StartStopPlaybackCC )
    {
        if( Session.GetStatus() == CSession::nStatus_Idle || 
            Session.GetStatus() == CSession::nStatus_Recording )
        {
            Session.StartPlayback();
        }
        else
        {
            Session.Stop();
        }
    }
    else if( number == Config.SelectNextTrackCC )
    {
        Session.SelectNextTrack();
    }
    else if( number == Config.SelectPreviousTrackCC )
    {
        Session.SelectPreviousTrack();
    }
}

void StartCB()
{
    DeltaClockCount = 0;
    Session.StartPlayback();
}

void StopCB()
{
    DeltaClockCount = 0;
    Session.Stop();
}

void ClockCB()
{
    Session.OnClock( );
    DeltaClockCount++;
}
