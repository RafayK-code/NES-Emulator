cmake_minimum_required(VERSION 3.3)
project("NesEmulator")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

add_subdirectory(external/SFML)

set(SOURCES
    src/main.cpp
    src/Bus.cpp 
    src/Bus.h 
    src/Cpu6502.cpp 
    src/Cpu6502.h
    src/Util.h
    src/Util.cpp
    src/Ppu2C02.h 
    src/Ppu2C02.cpp

    src/demo/CpuDemo.h 
    src/demo/CpuDemo.cpp 
    )

file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC external/SFML/include)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system sfml-graphics sfml-window)

target_include_directories(${PROJECT_NAME} PRIVATE src)