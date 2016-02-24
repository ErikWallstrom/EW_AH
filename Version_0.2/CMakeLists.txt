cmake_minimum_required(VERSION 2.8.9) #Because why not
project(C_Project)

include_directories(include)

if(WIN32)
	file(GLOB LINK_LIBS "lib/windows/*.dll")
elseif(UNIX AND NOT APPLE)
	file(GLOB LINK_LIBS "lib/linux/*.so")
else()
	message(SEND_ERROR "Platform not supported")
endif()
	
file(GLOB SOURCES "src/*.c")

add_definitions("-std=c11 -Wall -Wextra -Wshadow -Wpedantic -Wfatal-errors -ggdb3")

add_executable(Program ${SOURCES})
target_link_libraries(Program ${LINK_LIBS})
