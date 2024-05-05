cmake_minimum_required(VERISON 3.3)
project("NES-EM")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

set(SOURCES
    src/main.cpp)

add_executable(${PROJECT_NAME}, ${SOURCES})

