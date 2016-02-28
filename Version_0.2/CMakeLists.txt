cmake_minimum_required(VERSION 2.8.9) #Because why not
project(EW_AH)

include_directories(include)
file(GLOB SOURCES "src/*.c")

add_definitions("-std=c11 -Wall -Wextra -Wshadow -Wpedantic -Wfatal-errors -ggdb3")

if(WIN32)
	link_directories(build/windows /usr/lib)
	set(LIBRARIES SDL2 lua53)
elseif(UNIX AND NOT APPLE)
	link_directories(build/linux /usr/lib)
	set(LIBRARIES SDL2 SDL2_image SDL2_ttf SDL2_net SDL2_mixer lua53 m)
else()
	message(SEND_ERROR "Platform not supported")
endif()

add_executable(Program ${SOURCES})
target_link_libraries(Program ${LIBRARIES})
