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

#ifndef __SESSION_PLAYERCLIENT__
#define __SESSION_PLAYERCLIENT__

#include <Session/PlayerClient.h>
#include <Session/Event.h>
#include <Setup.h>

namespace NArduinoMIDILooper
{

class CPlayerClient
{

public:

    CPlayerClient();
    ~CPlayerClient();

    void Init();

    void PlayEvent( int channelID, const CEvent& e );
    void PlayEvent( int channelID, CEvent::EType type, char d1, char d2, char d3 );

private:

};

}

#endif
