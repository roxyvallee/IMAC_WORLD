cmake_minimum_required(VERSION 3.0)

project(ImacGL)

add_definitions(-std=c++11)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)
#set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/modules)

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

#find_package(SDL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(Eigen3 REQUIRED)
message(STATUS ${EIGEN3_INCLUDE_DIR})
message(STATUS ${EIGEN3_LIBRARY})


# For Apple
if (APPLE)
	include_directories(/usr/local/include)
endif (APPLE)

# For fac machine compilation
if(UPEMLV)
	set(OPENGL_LIBRARIES /usr/lib/x86_64-linux-gnu/libGL.so.1)
endif(UPEMLV)

include_directories(${SDL2_INCLUDE_DIRS})

# compilation flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2 -lSDL2 -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-g")

include_directories(${SDL2_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS} ${EIGEN3_INCLUDE_DIR} libs/glimac/include libs/imgui/include third-party/include)

set(ALL_LIBRARIES glimac imgui ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY})

#add the glimac library
add_subdirectory(libs/glimac)

#add the imgui library
add_subdirectory(libs/imgui)	

file(GLOB PJ_DIRECTORIES "src")

foreach(PJ ${PJ_DIRECTORIES})
    add_subdirectory(${PJ})
endforeach()
