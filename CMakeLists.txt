cmake_minimum_required(VERSION 3.4 FATAL_ERROR)
project(gravity_simulator LANGUAGES CXX)

find_package(SFML 2 REQUIRED COMPONENTS system window graphics)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    main.cpp
    object.cpp
    space.cpp)

add_executable(gravity_simulator ${SOURCES})
target_include_directories(gravity_simulator PRIVATE ${SFML_INCLUDE_DIR})
target_link_libraries(gravity_simulator ${SFML_LIBRARIES})
