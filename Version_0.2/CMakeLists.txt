cmake_minimum_required(VERSION 2.8.9) #Because why not
project(C_Project)

include_directories(include)
file(GLOB SOURCES "src/*.c")

add_definitions("-std=c11 -Wall -Wextra -Wshadow -Wpedantic -Wfatal-errors -ggdb3")

if(WIN32)
	link_directories(build/windows /usr/lib)
	set(LIBRARIES lua53)
elseif(UNIX AND NOT APPLE)
	link_directories(build/linux /usr/lib)
	set(LIBRARIES lua53 dl)
else()
	message(SEND_ERROR "Platform not supported")
endif()

add_executable(Program ${SOURCES})
target_link_libraries(Program ${LIBRARIES})
