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

#include <Session/Session.h>

using namespace NArduinoMIDILooper;

CSession::CSession() :
    m_CurrentTrack( 0 ),
    m_Status( CSession::nStatus_Idle ),
    m_CurrentBar( 0 ),
    m_BarCount( 0 ),
    m_CurrentQuarterNote( 0 ),
    m_QuarterNoteCount( 0 )
{

}

CSession::EStatus CSession::GetStatus() const
{
    return m_Status;
}

void CSession::StartRecord()
{
}

void CSession::StopRecord()
{
}

void CSession::StartPlayback()
{
}

void CSession::StopPlayback()
{
}

void CSession::SelectNextTrack()
{
    SelectTrack( m_CurrentTrack + 1 );
}

void CSession::SelectPreviousTrack()
{
    SelectTrack( m_CurrentTrack - 1 );
}

void CSession::SelectTrack( int n )
{
    if( n < 0 )
        m_CurrentTrack = 0;
    else if( n >= SESSION_TRACK_COUNT )
        m_CurrentTrack = SESSION_TRACK_COUNT - 1;
    else
        m_CurrentTrack = n;


    
}

void CSession::UpdatePlayback()
{
}

void CSession::Init()
{
    m_PlayerClient.Init();
    m_ListenerClient.Init();

    for( int i = 0; i<SESSION_TRACK_COUNT;i++ )
    {
        m_Tracks[i].Init();
    }
}

void CSession::Update()
{
    if( m_Status == nStatus_Playing )
    {
        UpdatePlayback();
    }
}
