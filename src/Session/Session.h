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

#ifndef __SESSION_SESSION__
#define __SESSION_SESSION__

#include <Session/Track.h>
#include <Session/Event.h>
#include <Utils/Timer.h>
#include <Utils/Singleton.h>
#include <Setup.h>

#define Session (CSession::GetInstance())

namespace NArduinoMIDILooper
{

class CSession : public CSingleton<CSession>
{

public:

    enum EStatus
    {
        nStatus_Recording = 0,
        nStatus_Playing,
        nStatus_WaitingBeforePlaying,
        nStatus_Idle,
        nStatus_Count
    };

    CSession();
    ~CSession();

    EStatus GetStatus() const;

    void StartRecord();
    void StartPlayback();
    void Stop();
    void SelectNextTrack();
    void SelectPreviousTrack();
    void SelectTrack( int n );
    void SetTrackMIDIChannel( int track, int channel );
    int  GetTrackMIDIChannel( int track );

    void Init();

    void OnEvent( const CEvent& e );
    void OnClock();

private:

    void UpdatePlayback();
    void UpdateQuarterNoteDuration();
    void Reset();
    void PlayEvent( const CEvent& e );
    void PlayEvent( CEvent::EType type, char d1, char d2 );

    CTrack          m_Tracks[SESSION_TRACK_COUNT];
    int             m_CurrentTrack;
    EStatus         m_Status;
    CTimer          m_Timer;

    CEvent          m_NextEvent;
    int             m_NextEventIndex;

    Time            m_QuarterNoteDuration;
    unsigned int    m_CurrentQuarterNote;
    unsigned int    m_QuarterNoteCount;
    ClockCount      m_ClockCount;
    ClockCount      m_DeltaClockCount;
};

}

#endif
