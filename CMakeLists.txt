set(CMAKE_SYSTEM_NAME Generic)

set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_CXX_COMPILER avr-g++)

cmake_minimum_required(VERSION 2.6)
project(AruduinoMIDILooper)

set(COPT "-Os -fshort-enums")
set(CWARN "-Wall")
set(CSECTION "-ffunction-sections -fdata-sections")
set(CMCU "-mmcu=atmega328p")
set(CDEFS "-DF_CPU=16000000L -MMD -DUSB_VID=null -DUSB_PID=null -DARDUINO=105")
set(CXXTUNING "-fno-exceptions")

set(CFLAGS "${COPT} ${CWARN} ${CSECTIONS} ${CMCU} ${CDEFS}")
set(CXXFLAGS "${COPT} ${CXXTUNING} ${CWARN} ${CSECTIONS} ${CMCU} ${CDEFS}")

set(CMAKE_EXE_LINKER_FLAGS "-Wl,--gc-sections -nodefaultlibs")

set(CMAKE_C_FLAGS ${CFLAGS})
set(CMAKE_CXX_FLAGS ${CXXFLAGS})

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")
include_directories($ENV{ARDUINO_INCLUDE})
link_directories($ENV{ARDUINO_LIB})

add_executable( ArduinoMIDILooper 
  src/Main.cpp 

  src/Utils/Timer.cpp

  src/Application/Application.cpp 
  src/Application/ListenerServer.cpp 
  src/Application/PlayerServer.cpp 
  src/Application/Logger.cpp
  src/Application/MemoryManager.cpp
  src/Application/InputReader.cpp

  src/Session/Session.cpp
  src/Session/Track.cpp
  src/Session/Event.cpp

  )

# Custom POST_BUILD target to call avr-objcopy over the generated elf file
add_custom_command( TARGET ArduinoMIDILooper POST_BUILD COMMAND avr-objcopy -O ihex -R .eeprom ArduinoMIDILooper ArduinoMIDILooper.hex )

# Target to transfert compiled .hex file to the arduino connected on /dev/ttyACM0
add_custom_target( transfert COMMAND sudo avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:ArduinoMIDILooper.hex )

# Target to setup serial communication over /dev/ttyACM0
add_custom_target( setupserial COMMAND stty -F /dev/ttyACM0 cs8 9600 ignbrk -brkint -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts )

# Link order has defined here is not randomly chossen:
# libm.a must be linked at the end to avoid duplaicated symbol
# libc.a msut be included twice otherwise i get the relocation truncated to fit: R_AVR_13_PCREL against symbol `__ctype_isfalse' error 
# This order was found by testing and trying, this is not a good solution but it works ... for now
target_link_libraries( ArduinoMIDILooper c) 
target_link_libraries( ArduinoMIDILooper ArduinoCore) 
target_link_libraries( ArduinoMIDILooper ArduinoSPIRAM) 
target_link_libraries( ArduinoMIDILooper ArduinoSPI) 
target_link_libraries( ArduinoMIDILooper ArduinoMIDI) 
target_link_libraries( ArduinoMIDILooper c) 
target_link_libraries( ArduinoMIDILooper gcc) 
target_link_libraries( ArduinoMIDILooper m) 





