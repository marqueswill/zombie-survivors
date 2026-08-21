cmake_minimum_required(VERSION 3.16)

project(ZombieSurvivors VERSION 1.0 LANGUAGES CXX)
option(MYGAME_VENDORED "Use vendored libraries" ON)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

if(MYGAME_VENDORED)
# This assumes the SDL source is available in vendored/SDL
add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)
else()
    find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
endif()

# Create your game executable target as usual
add_executable(zombie_survivors ./src/main.cpp)

# Link to the actual SDL3 library.
target_link_libraries(zombie_survivors PRIVATE SDL3::SDL3)