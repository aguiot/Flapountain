cmake_minimum_required(VERSION 2.8)

find_package(OpenGL REQUIRED)
find_package(OpenCV REQUIRED )

find_path(SDL2_INCLUDE_DIR NAMES SDL.h PATH_SUFFIXES SDL2)
find_library(SDL2_LIBRARY NAMES SDL2 PATH_SUFFIXES x64 x86)

find_path(SDL2IMAGE_INCLUDE_DIR NAMES SDL_image.h PATH_SUFFIXES SDL2)
find_library(SDL2IMAGE_LIBRARY NAMES SDL_image PATH_SUFFIXES x64 x86)
string(REPLACE "SDL" "SDL2" SDL2IMAGE_LIBRARY ${SDL2IMAGE_LIBRARY})

include_directories(${OPENGL_INCLUDE_DIR} ${SDL2_INCLUDE_DIR} ${SDL2IMAGE_INCLUDE_DIR} ${ASSIMP_INCLUDE_DIR})

include_directories(glm: third-party)
include_directories(third-party/glew-1.10.0/include)
add_definitions(-DGLEW_STATIC=1)
add_subdirectory(third-party/glew-1.10.0)

set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs")

include_directories(lib/include)
add_subdirectory(lib)

set(ALL_LIBRARIES glew ${OPENGL_LIBRARIES} ${SDL2_LIBRARY} ${SDL2IMAGE_LIBRARY} ${OpenCV_LIBS} ${ASSIMP_LIBRARY} glimac)

add_subdirectory(Main)
