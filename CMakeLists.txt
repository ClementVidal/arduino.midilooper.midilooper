set(CMAKE_SYSTEM_NAME Generic)

set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_CXX_COMPILER avr-gxx)

cmake_minimum_required(VERSION 2.6)
project(AruduinoMIDI)

set(COPT "-g -Os")
set(CWARN "-Wall")
set(CSECTION "-ffunction-sections -fdata-sections")
set(CMCU "-mmcu=atmega328p")
set(CDEFS "-DF_CPU=16000000L -MMD -DUSB_VID=null -DUSB_PID=null -DARDUINO=105")
set(CXXTUNING "-fno-exceptions")

set(CFLAGS "${COPT} ${CWARN} ${CSECTIONS} ${CMCU} ${CDEFS}")
set(CXXFLAGS "${COPT} ${CXXTUNING} ${CWARN} ${CSECTIONS} ${CMCU} ${CDEFS}")

set(CMAKE_EXE_LINKER_FLAGS "-Wl,--gc-sections")

set(CMAKE_C_FLAGS ${CFLAGS})
set(CMAKE_CXX_FLAGS ${CXXFLAGS})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories("/home/cvidal/Dev/ArduinoLib/install/include/Arduino")
link_directories ("/home/cvidal/Dev/ArduinoLib/install/lib/static/")

add_executable( ArduinoMIDILooper src/main.cpp )

add_custom_command( TARGET ArduinoMIDILooper POST_BUILD COMMAND avr-objcopy -O ihex -R .eeprom ArduinoMIDILooper ArduinoMIDILooper.hex )

add_custom_target( transfert COMMAND sudo avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:ArduinoMIDILooper.hex )

add_custom_target( setupserial COMMAND stty -F /dev/ttyACM0 cs8 9600 ignbrk -brkint -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts )

target_link_libraries( ArduinoMIDILooper ArduinoCore) 
target_link_libraries( ArduinoMIDILooper m) 