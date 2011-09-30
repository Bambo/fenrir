#I just wanted to inform everyone that CMake's "uppercase attitude" is driving me nuts.
cmake_minimum_required(VERSION 2.8)
project(fenrir)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions -fno-rtti") #I don't use exceptions, save some space.
	if(NOT WIN32) # GCC doesn't give a fuck, or so it claims
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden -fvisibility-inlines-hidden") # Save some space.
	endif()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")
endif()

if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /GS- /GR-")
endif()



find_package(PhysFS REQUIRED)
find_package(Lua51 REQUIRED)
include_directories(include ${LUA_INCLUDE_DIR})
add_subdirectory(src)
