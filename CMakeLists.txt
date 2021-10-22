cmake_minimum_required(VERSION 3.10)

project(ascii-game)

include(FetchContent)

set(BUILD_SHARED_LIBS OFF)
FetchContent_Declare(
 SFML
 GIT_REPOSITORY https://github.com/SFML/SFML.git
 GIT_TAG 2.5.1
)
FetchContent_MakeAvailable(SFML)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

set(EXECUTABLE_NAME ascii-game)
add_executable(${EXECUTABLE_NAME} "ASCII-Game/main.cpp")
target_link_libraries(${EXECUTABLE_NAME} sfml-audio)
