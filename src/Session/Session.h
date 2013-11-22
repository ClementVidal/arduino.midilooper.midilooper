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
#include <Session/PlayerClient.h>
#include <Session/ListenerClient.h>
#include <Setup.h>

namespace NArduinoMIDILooper
{

class CSession
{

public:

    enum EStatus
    {
        nStatus_Recording = 0,
        nStatus_Playing,
        nStatus_Idle,
        nStatus_Count
    };

    CSession();
    ~CSession();

    EStatus GetStatus() const;

    void StartRecord();
    void StopRecord();
    void StartPlayback();
    void StopPlayback();
    void SelectNextTrack();
    void SelectPreviousTrack();
    void SelectTrack( int n );

    void Init();
    void Update();

private:

    void UpdatePlayback();

    CPlayerClient   m_PlayerClient;
    CListenerClient m_ListenerClient;
    CTrack     m_Tracks[SESSION_TRACK_COUNT];
    int        m_CurrentTrack;
    EStatus    m_Status;

    int        m_CurrentBar;
    int        m_BarCount;
    int        m_CurrentQuarterNote;
    int        m_QuarterNoteCount;

};

}

#endif
