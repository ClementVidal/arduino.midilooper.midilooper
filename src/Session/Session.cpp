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
    m_CurrentQuarterNote( -1 ),
    m_QuarterNoteCount( 0 ),
    m_ClockCount( 0 )
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
    if( m_Status == nStatus_Idle )
        return;

    if( m_Status == nStatus_Recording )
    {
        CTrack* currentTrack = &m_Tracks[m_CurrentTrack];
        currentTrack->AddEvent( e );
    }

    PlayEvent( e );
}

void CSession::OnClock( )
{
    m_ClockCount++;
    if( m_ClockCount == CLOCK_PER_QUARTER_NOTE ) 
    {
        m_QuarterNoteCount++;
        m_ClockCount = 0;
    }
}

void CSession::PlayEvent( const CEvent& e )
{
    PlayEvent( e.Type, e.Data[0], e.Data[1], e.Data[2] );
}

void CSession::PlayEvent( CEvent::EType type, char d1, char d2, char d3 )
{
    CTrack* currentTrack = &m_Tracks[m_CurrentTrack];
    MIDIPlayer.PlayEvent( currentTrack->GetChannelID(), type, d1, d2, d3 );
}

void CSession::Reset()
{
    m_Timer.Stop();
    m_Status = CSession::nStatus_Idle;
    m_NextEventIndex = -1 ;
    m_CurrentQuarterNote = -1;
    m_QuarterNoteCount = 0 ;
    m_ClockCount = 0;
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

    int tmpQNCount = m_QuarterNoteCount;
    Reset();
    m_QuarterNoteCount = tmpQNCount;
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

    int tmpQNCount = m_QuarterNoteCount;
    Reset();
    m_QuarterNoteCount = tmpQNCount;    

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
    int nt = 0;

    if( n < 0 )
        nt = 0;
    else if( n >= SESSION_TRACK_COUNT )
        nt = SESSION_TRACK_COUNT - 1;
    else
        nt = n;
    
    if( m_CurrentTrack != nt )
    {
        Reset();
        m_CurrentTrack = nt;
    }
}

void CSession::UpdatePlayback()
{
    Time t = m_Timer.GetElapsedTimeSinceLastTag();
    CTrack* currentTrack = &m_Tracks[m_CurrentTrack];

    if( t >= m_NextEvent.DeltaTime )
    {
        PlayEvent( m_NextEvent );
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
