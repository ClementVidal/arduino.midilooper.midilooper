
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

#include <Application/Config.h>

#include <DataType.h>

#include <EEPROM.h>

using namespace NArduinoMIDILooper;

CConfig::CConfig() :
    StartStopRecordCC( CONFIG_DEFAULT_STARTSTOPRECORDCC ),
    StartStopPlaybackCC( CONFIG_DEFAULT_STARTSTOPPLAYBACKCC ),
    SelectNextTrackCC( CONFIG_DEFAULT_NEXT_TRACKCC ),
    SelectPreviousTrackCC( CONFIG_DEFAULT_PREVIOUS_TRACKCC ),
    MIDIInputChannel( CONFIG_DEFAULT_INPUT_CHANNEL )
{

}

CConfig::~CConfig()
{

}

void CConfig::Init()
{
    int value = 0;
    value = EEPROM.read( 0 );

    if( value != EEPROM_MAGIC_KEY )
        return;

    StartStopRecordCC = EEPROM.read( 1 );
    StartStopPlaybackCC = EEPROM.read( 2 );
    SelectNextTrackCC = EEPROM.read( 3 );
    SelectPreviousTrackCC = EEPROM.read( 4 );
    MIDIInputChannel = EEPROM.read( 5 );

}
