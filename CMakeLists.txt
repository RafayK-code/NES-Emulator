cmake_minimum_required(VERSION 3.3)
project("NesEmulator")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(external/SFML)

set(SOURCES
    src/main.cpp
    src/Bus.cpp 
    src/Bus.h 
    src/Cpu6502.cpp 
    src/Cpu6502.h
    )

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC external/SFML/include)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system sfml-graphics sfml-window)