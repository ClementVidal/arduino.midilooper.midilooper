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

#ifndef __APPLICATION_OUTPUTMANAGER__
#define __APPLICATION_OUTPUTMANAGER__

#include <Utils/Singleton.h>

#include <LiquidCrystal.h>

#define OutputManager (COutputManager::GetInstance())

namespace NArduinoMIDILooper
{

class COutputManager : public CSingleton<COutputManager>
{

public:

    COutputManager();
    ~COutputManager();

    void Init();

private:

    LiquidCrystal m_LiquidCrystal;

};

}

#endif
