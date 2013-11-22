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

#include <Utils/Timer.h>

#include <Arduino.h>

using namespace NArduinoMIDILooper;

CTimer::CTimer() :
    m_StartTime( 0 ),
    m_TagTime( 0 )
{

}

CTimer::~CTimer()
{

}

void CTimer::Start()
{
    m_StartTime = millis();
    m_TagTime = m_StartTime;
}

void CTimer::Stop()
{
}

void CTimer::Tag()
{
    if( m_StartTime == 0 )
        return;

    m_TagTime = millis();
}

Time CTimer::GetElapsedTimeSinceLastTag( bool tagAfter )
{
    Time t2 = millis();
    Time t1 = m_TagTime;
    
    if( tagAfter )
        m_TagTime = t2;

    return t2-t1;
}

Time CTimer::GetElapsedTimeSinceStart()
{
    Time t2 = millis();
    Time t1 = m_StartTime;
    
    return t2-t1;
}
