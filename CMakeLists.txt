cmake_minimum_required(VERSION 3.5)
project(SolarSystem)

if(NOT CMAKE_BUILD_TYPE)
    set(MAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(WIN32)
    set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs/SFML-2.6.2_win/lib/cmake/SFML")
endif()

if(UNIX)
    set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs/SFML-2.6.2_lin/lib/cmake/SFML")
endif()

find_package(SFML COMPONENTS graphics window system REQUIRED)

add_executable(${PROJECT_NAME} 
    src/main.cpp 
    src/Planet.cpp 
    src/Universe.cpp
)

if(MSVC)
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
endif()

target_include_directories(${PROJECT_NAME} PRIVATE src)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window sfml-system)