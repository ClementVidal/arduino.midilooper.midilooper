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

#include <Session/Track.h>
#include <Session/Event.h>
#include <Application/MemoryManager.h>
#include <Setup.h>

using namespace NArduinoMIDILooper;

CTrack::CTrack() :
    m_ChannelID( 0 ),
    m_EventCount( 0 ),
    m_EventsStartAddress( 0 )
{
}

CTrack::~CTrack()
{

}

int CTrack::GetChannelID() const
{
    return m_ChannelID;
}

void CTrack::SetChannelID( int channelID )
{
    m_ChannelID = channelID;
}

void CTrack::Init()
{
    m_EventsStartAddress = (CEvent*)MemoryManager.Reserve( sizeof( CEvent ) * TRACK_EVENT_COUNT );
}

void CTrack::GetEvent( int index, CEvent& e )
{
    MemoryManager.Read( & m_EventsStartAddress[index], &e, sizeof( CEvent ) );
}

void CTrack::AddEvent( const CEvent& e )
{
    MemoryManager.Write( & m_EventsStartAddress[m_EventCount], &e, sizeof( CEvent ) );
}

void CTrack::Clear()
{
    m_EventCount = 0;
}

int CTrack::GetEventCount() const
{
    return m_EventCount;
}
