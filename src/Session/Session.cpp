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
#include <Application/MIDIPlayer.h>

using namespace NArduinoMIDILooper;

CSession::CSession() :
    m_CurrentTrack( 0 ),
    m_Status( CSession::nStatus_Idle ),
    m_NextEventIndex( -1 ),
    m_CurrentBar( -1 ),
    m_BarCount( -1 ),
    m_CurrentQuarterNote( -1 ),
    m_QuarterNoteCount( -1 )
{

}

CSession::~CSession()
{
}

CSession::EStatus CSession::GetStatus() const
{
    return m_Status;
}

void CSession::OnEvent( const CEvent& e )
{
}

void CSession::PlayEvent( int channelID, const CEvent& e )
{
    PlayEvent( channelID, e.Type, e.Data[0], e.Data[1], e.Data[2] );
}

void CSession::PlayEvent( int channelID, CEvent::EType type, char d1, char d2, char d3 )
{
    MIDIPlayer.PlayEvent( channelID, type, d1, d2, d3 );
}

void CSession::Reset()
{
    m_Timer.Stop();
    m_Status = CSession::nStatus_Idle;
    m_NextEventIndex = -1 ;
    m_CurrentBar = -1;
    m_BarCount = -1;
    m_CurrentQuarterNote = -1;
    m_QuarterNoteCount = -1 ;
}

void CSession::StartRecord()
{
    Reset();
    m_Timer.Start();
    m_Status = nStatus_Recording;
}

void CSession::Stop()
{
    if( m_Status == nStatus_Idle )
        return;

    int tmpBarCount = m_BarCount;
    Reset();
    m_BarCount = tmpBarCount;
}

void CSession::StartPlayback()
{
    if( m_Status == nStatus_Recording )
    {
        Stop();
    }
    else if( m_Status == nStatus_Playing )
    {
        return;
    }

    int tmpBarCount = m_BarCount;
    Reset();
    m_BarCount = tmpBarCount;    

    m_Status = nStatus_Playing;
    m_Timer.Start();

    m_NextEventIndex = 0;
    m_Tracks[m_CurrentTrack].GetEvent( m_NextEventIndex, m_NextEvent );
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
    Time t = m_Timer.GetElapsedTimeSinceLastTag();
    CTrack* currentTrack = &m_Tracks[m_CurrentTrack];

    if( t >= m_NextEvent.DeltaTime )
    {
        PlayEvent( currentTrack->GetChannelID(), m_NextEvent );
        m_Timer.Tag();
        
        m_NextEventIndex++;

        if( m_NextEventIndex >= currentTrack->GetEventCount() )
        {
            m_NextEventIndex = 0;
        }

        currentTrack->GetEvent( m_NextEventIndex, m_NextEvent );
    }
}

void CSession::Init()
{
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
