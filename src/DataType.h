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

#ifndef __DATATYPES__
#define __DATATYPES__


#define CLOCK_PER_QUARTER_NOTE (24)
#define EEPROM_MAGIC_KEY (0xBB)

#define CONFIG_DEFAULT_STARTCC 32
#define CONFIG_DEFAULT_NEXT_TRACKCC 33
#define CONFIG_DEFAULT_PREVIOUS_TRACKCC 34
#define CONFIG_DEFAULT_INPUT_CHANNEL 0

typedef unsigned long Time; // Time MUST be 4 bytes long
typedef unsigned int ClockCount; // Time MUST be 2 bytes long



#endif
