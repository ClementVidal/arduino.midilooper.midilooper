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

#ifndef __APPLICATION_USERINTERFACE__
#define __APPLICATION_USERINTERFACE__

#include <Utils/Singleton.h>

#include <LiquidCrystal.h>

#define UserInterface (CUserInterface::GetInstance())

namespace NArduinoMIDILooper
{

class CUserInterface : public CSingleton<CUserInterface>
{

public:

    enum EButton
    {
        nButton_Left = 0,
        nButton_Right,
        nButton_Up,
        nButton_Down
    };

    enum EMenu
    {
        nMenu_ActiveTrack = 1,

        nMenu_Settings,
        nMenu_StartRecordCC,
        nMenu_NextTrackCC,
        nMenu_PreviousTrackCC,
        nMenu_MIDIInputChannel,

        nMenu_TrackMIDIChannel,
        nMenu_Track1MIDIChannel,
        nMenu_Track2MIDIChannel,
        nMenu_Track3MIDIChannel,
        nMenu_Track4MIDIChannel,

        nMenu_Info,
        nMenu_Set,
        nMenu_None
    };

    enum EState
    {
        nState_Navigation = 0,
        nState_SetMIDIChannel,
        nState_SetMIDICC,
        nState_SetTrack

    };

    enum EMenuCount
    {
        nMenuCount_TopLevel = 3,
        nMenuCount_Settings = 4,
        nMenuCount_TrackMIDIChannel = 4
    };

    CUserInterface();
    ~CUserInterface();

    void Init();
    void Update();

private:

    void OnButtonPressed( EButton btn );
    void RefreshDisplay();
    void EnterSetValueState();
    void ValidateSelection();
    void CancelSelection();
    void SelectNextValue();
    void SelectPreviousValue();

    EState        m_State;
    EMenu         m_CurrentMenu;
    int           m_SelectedValue;
    LiquidCrystal m_LiquidCrystal;

};

}

#endif
