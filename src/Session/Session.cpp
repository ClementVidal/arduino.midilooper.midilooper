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
    m_QuarterNoteDuration( 0 ),
    m_CurrentQuarterNote( -1 ),
    m_QuarterNoteCount( 0 ),
    m_ClockCount( 0 ),
    m_DeltaClockCount( 0 )
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
    if( m_Status == nStatus_Playing )
    {
        if( m_ClockCount == 0 ) 
        {
            m_DeltaClockCount = 0;
        }

        UpdatePlayback();

        m_DeltaClockCount++;
    }
    // Real playback start begin after the first Clock received
    else if( m_Status == nStatus_WaitingBeforePlaying )
    {
        m_Status = nStatus_Playing;
        m_Timer.Start();
    }

    UpdateQuarterNoteDuration();
}

void CSession::PlayEvent( const CEvent& e )
{
    PlayEvent( e.Type, e.ByteData[0], e.ByteData[1] );
}

void CSession::PlayEvent( CEvent::EType type, char d1, char d2 )
{
    CTrack* currentTrack = &m_Tracks[m_CurrentTrack];
    MIDIPlayer.PlayEvent( currentTrack->GetMIDIChannel(), type, d1, d2 );
}

void CSession::Reset()
{
    m_Timer.Stop();
    m_Status = CSession::nStatus_Idle;
    m_NextEventIndex = -1 ;
    m_CurrentQuarterNote = -1;
    m_QuarterNoteCount = 0 ;
    m_ClockCount = 0;
    m_DeltaClockCount = 0;
    m_QuarterNoteDuration = 0;
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
    {
        return;
    }

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
    else if( m_Status == nStatus_Playing || m_Status == nStatus_WaitingBeforePlaying )
    {
        return;
    }

    int tmpQNCount = m_QuarterNoteCount;
    Reset();
    m_QuarterNoteCount = tmpQNCount;    

    m_Status = nStatus_WaitingBeforePlaying;

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
    {
        nt = 0;
    }
    else if( n >= SESSION_TRACK_COUNT )
    {
        nt = SESSION_TRACK_COUNT - 1;
    }
    else
    {
        nt = n;
    }
    
    if( m_CurrentTrack != nt )
    {
        Reset();
        m_CurrentTrack = nt;
    }
}

void CSession::UpdateQuarterNoteDuration()
{
    static Time s_QNTime = 0;

    if( m_ClockCount == 0 ) 
    {
        s_QNTime = m_Timer.GetElapsedTimeSinceStart();
    }

    if( m_ClockCount == CLOCK_PER_QUARTER_NOTE ) 
    {
        Time t = m_Timer.GetElapsedTimeSinceStart();
        m_QuarterNoteDuration = t - s_QNTime;
        s_QNTime = t;
        m_QuarterNoteCount++;
        m_ClockCount = 0;
    }

    m_ClockCount++;
}

void CSession::UpdatePlayback()
{
    CTrack* currentTrack = &m_Tracks[m_CurrentTrack];

    int playedEventCount = 0;
    int nextEventIndex = m_NextEventIndex;

    while( m_DeltaClockCount >= m_NextEvent.DeltaClockCount  )
    {
        // Play event
        PlayEvent( m_NextEvent );
        playedEventCount++;

        // Move to next event or loop if necessary
        nextEventIndex++;
        if( nextEventIndex >= currentTrack->GetEventCount() )
        {
            nextEventIndex = 0;
        }

        // This mean that we are going to fetch an event that was already played
        if( nextEventIndex == m_NextEventIndex )
        {
            break;
        }

        // Fetch next event
        currentTrack->GetEvent( nextEventIndex, m_NextEvent );
    }

    // Reset delta clock if at least one Event was played
    if( playedEventCount != 0 )
    {
        m_DeltaClockCount = 0;
        m_NextEventIndex = nextEventIndex;
    }

}

void CSession::Init()
{
    for( int i = 0; i<SESSION_TRACK_COUNT;i++ )
    {
        m_Tracks[i].Init();
    }
}

void CSession::SetTrackMIDIChannel( int track, int channel )
{
    if( track >= 0 && track < SESSION_TRACK_COUNT )
    {
        m_Tracks[track].SetMIDIChannel( channel );
    }
}

int CSession::GetTrackMIDIChannel( int track )
{
    if( track >= 0 && track < SESSION_TRACK_COUNT )
    {
        return m_Tracks[track].GetMIDIChannel( );
    }

    return -1;
}
