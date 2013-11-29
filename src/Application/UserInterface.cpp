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

#include <Application/UserInterface.h>
#include <Application/Config.h>
#include <Session/Session.h>
#include <Setup.h>

using namespace NArduinoMIDILooper;

static CUserInterface::EMenu MenuNavigationMatrix[12][4] =
{
//    |             Left                      |             Right                     |             Up                        |             Down     
    {  CUserInterface::nMenu_None,             CUserInterface::nMenu_Settings,         CUserInterface::nMenu_None,             CUserInterface::nMenu_Set },               //nMenu_ActiveTrack
    {  CUserInterface::nMenu_ActiveTrack,      CUserInterface::nMenu_TrackMIDIChannel, CUserInterface::nMenu_None,             CUserInterface::nMenu_StartRecordCC },     //nMenu_Settings
    {  CUserInterface::nMenu_Settings,         CUserInterface::nMenu_Info,             CUserInterface::nMenu_None,             CUserInterface::nMenu_Track1MIDIChannel }, //nMenu_TrackMIDIChannel
    {  CUserInterface::nMenu_TrackMIDIChannel, CUserInterface::nMenu_None,             CUserInterface::nMenu_None,             CUserInterface::nMenu_Set },               //nMenu_Info

    {  CUserInterface::nMenu_None,             CUserInterface::nMenu_NextTrackCC,      CUserInterface::nMenu_Settings,         CUserInterface::nMenu_Set },              //nMenu_StartRecordCC
    {  CUserInterface::nMenu_StartRecordCC,    CUserInterface::nMenu_PreviousTrackCC,  CUserInterface::nMenu_Settings,         CUserInterface::nMenu_Set },              //nMenu_NextTrackCC
    {  CUserInterface::nMenu_NextTrackCC,      CUserInterface::nMenu_MIDIInputChannel, CUserInterface::nMenu_Settings,         CUserInterface::nMenu_Set },              //nMenu_PreviousTrackCC
    {  CUserInterface::nMenu_PreviousTrackCC,  CUserInterface::nMenu_None,             CUserInterface::nMenu_Settings,         CUserInterface::nMenu_Set },              //nMenu_StartRecordCC

    {  CUserInterface::nMenu_None,             CUserInterface::nMenu_Track2MIDIChannel,CUserInterface::nMenu_TrackMIDIChannel, CUserInterface::nMenu_Set },              //nMenu_Track1MIDIChannel
    {  CUserInterface::nMenu_Track1MIDIChannel,CUserInterface::nMenu_Track3MIDIChannel,CUserInterface::nMenu_TrackMIDIChannel, CUserInterface::nMenu_Set },              //nMenu_Track2MIDIChannel
    {  CUserInterface::nMenu_Track2MIDIChannel,CUserInterface::nMenu_Track4MIDIChannel,CUserInterface::nMenu_TrackMIDIChannel, CUserInterface::nMenu_Set },              //nMenu_Track3MIDIChannel
    {  CUserInterface::nMenu_Track3MIDIChannel,CUserInterface::nMenu_None,             CUserInterface::nMenu_TrackMIDIChannel, CUserInterface::nMenu_Set },              //nMenu_Track4MIDIChannel

};

CUserInterface::CUserInterface() :
    m_State( nState_Navigation ),
    m_CurrentMenu( nMenu_ActiveTrack ),
    m_SelectedValue( 0 ),
    m_LiquidCrystal()
{

}

CUserInterface::~CUserInterface()
{

}

void CUserInterface::Init()
{

}

void CUserInterface::Update()
{

}

void CUserInterface::RefreshDisplay()
{
    if( m_State == nState_SetMIDIChannel )
    {
        m_LiquidCrystal.setCursor( 0, 0 );
        m_LiquidCrystal.print("MIDI Channel: ");    
    }
    else if( m_State == nState_SetMIDICC )
    {
        m_LiquidCrystal.setCursor( 0, 0 );
        m_LiquidCrystal.print("MIDI CC: ");    
    }
    else if( m_State == nState_SetTrack )
    {
        m_LiquidCrystal.setCursor( 0, 0 );
        m_LiquidCrystal.print("Track: ");    
    }

    m_LiquidCrystal.setCursor( 0, 1 );
    m_LiquidCrystal.print(m_SelectedValue);    
}

void CUserInterface::EnterSetValueState()
{
    if( m_CurrentMenu == nMenu_Track1MIDIChannel || m_CurrentMenu == nMenu_Track2MIDIChannel || 
        m_CurrentMenu == nMenu_Track3MIDIChannel || m_CurrentMenu == nMenu_Track4MIDIChannel)
    {
        m_SelectedValue = Session.GetTrackMIDIChannel( nMenu_Track1MIDIChannel - m_CurrentMenu );
        m_State = nState_SetMIDIChannel;
    }
    else if( m_CurrentMenu == nMenu_PreviousTrackCC || m_CurrentMenu == nMenu_NextTrackCC || 
             m_CurrentMenu == nMenu_StartRecordCC )
    {
        if( m_CurrentMenu == nMenu_PreviousTrackCC )
        {
            m_SelectedValue = Config.SelectPreviousTrackCC;
        }
        else if( m_CurrentMenu == nMenu_NextTrackCC )
        {
            m_SelectedValue = Config.SelectNextTrackCC;
        }
        else if( m_CurrentMenu == nMenu_StartRecordCC )
        {
            m_SelectedValue = Config.StartRecordCC;
        }
        m_State = nState_SetMIDICC;
    }
    if( m_CurrentMenu == nMenu_MIDIInputChannel )
    {
        m_SelectedValue = Config.MIDIInputChannel;
        m_State = nState_SetMIDIChannel;
    }

    RefreshDisplay();
}

void CUserInterface::SelectNextValue()
{
    if( m_State ==  nState_SetMIDIChannel )
    {
        if( m_SelectedValue + 1 > 16 )
            return;

        m_SelectedValue ++;
    }
    else if( m_State ==  nState_SetMIDICC )
    {
        if( m_SelectedValue + 1 > 127 )
            return;

        m_SelectedValue ++;
    }
    else if( m_State ==  nState_SetTrack )
    {
        if( m_SelectedValue + 1 > 3 )
            return;

        m_SelectedValue ++;
    }

    RefreshDisplay();
}

void CUserInterface::SelectPreviousValue()
{
    if( m_State ==  nState_SetMIDIChannel )
    {
        if( m_SelectedValue - 1 <= 0 )
            return;

        m_SelectedValue --;
    }
    else if( m_State ==  nState_SetMIDICC )
    {
        if( m_SelectedValue - 1 < 0 )
            return;

        m_SelectedValue --;
    }
    else if( m_State ==  nState_SetTrack )
    {
        if( m_SelectedValue - 1 < 0 )
            return;

        m_SelectedValue --;
    }

    RefreshDisplay();
}

void CUserInterface::CancelSelection()
{
    m_SelectedValue = 0;
    m_State = nState_Navigation;
    RefreshDisplay();
}

void CUserInterface::ValidateSelection()
{
    if( m_CurrentMenu == nMenu_Track1MIDIChannel || m_CurrentMenu == nMenu_Track2MIDIChannel || 
        m_CurrentMenu == nMenu_Track3MIDIChannel || m_CurrentMenu == nMenu_Track4MIDIChannel)
    {
        Session.SetTrackMIDIChannel( nMenu_Track1MIDIChannel - m_CurrentMenu, m_SelectedValue ); 
    }
    else if( m_CurrentMenu == nMenu_PreviousTrackCC || m_CurrentMenu == nMenu_NextTrackCC || 
             m_CurrentMenu == nMenu_StartRecordCC )
    {
        if( m_CurrentMenu == nMenu_PreviousTrackCC )
        {
            Config.SelectPreviousTrackCC = m_SelectedValue;
        }
        else if( m_CurrentMenu == nMenu_NextTrackCC )
        {
            Config.SelectNextTrackCC = m_SelectedValue;
        }
        else if( m_CurrentMenu == nMenu_StartRecordCC )
        {
            Config.StartRecordCC = m_SelectedValue;
        }        
    }
    if( m_CurrentMenu == nMenu_MIDIInputChannel )
    {
        Config.MIDIInputChannel = m_SelectedValue;
    }

    m_SelectedValue = 0;
    m_State = nState_Navigation;
    RefreshDisplay();
}

void CUserInterface::OnButtonPressed( CUserInterface::EButton btn )
{
    if( m_State == nState_Navigation )
    {
        EMenu nextMenu = MenuNavigationMatrix[m_CurrentMenu][btn];
        
        if( nextMenu != nMenu_None && nextMenu != nMenu_Set )
        {
            m_CurrentMenu = nextMenu;
            RefreshDisplay();
        }
        else if( nextMenu == nMenu_Set )
        {
            EnterSetValueState( );
        }
    }
    else
    {
        if( btn == nButton_Down )
        {
            ValidateSelection();
        }
        else if( btn == nButton_Up )
        {
            CancelSelection();
        }
        else if( btn == nButton_Left )
        {
            SelectPreviousValue();
        }
        else if( btn == nButton_Right )
        {
            SelectNextValue();
        }
    }
}
