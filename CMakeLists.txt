cmake_minimum_required(VERSION 3.10)
project(SolarSystem)

if(NOT CMAKE_BUILD_TYPE)
    set(MAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Ручная настройка SFML (самый надежный способ)
set(SFML_ROOT "${CMAKE_SOURCE_DIR}/SFML-2.6.2")
set(SFML_INCLUDE_DIR "${SFML_ROOT}/include")
set(SFML_LIB_DIR "${SFML_ROOT}/lib")

# Проверка существования SFML
if(NOT EXISTS "${SFML_ROOT}")
    message(FATAL_ERROR "SFML not found at: ${SFML_ROOT}. Please make sure SFML-2.6.2 is in the project directory.")
endif()

if(NOT EXISTS "${SFML_INCLUDE_DIR}/SFML")
    message(FATAL_ERROR "SFML include files not found in: ${SFML_INCLUDE_DIR}")
endif()

message(STATUS "SFML found at: ${SFML_ROOT}")

# Создаем исполняемый файл
add_executable(Solar_System 
    main.cpp 
    Planet.cpp 
    Universe.cpp
    # Добавьте другие .cpp файлы вашего проекта
)

# Include директории (текущая папка и SFML)
target_include_directories(Solar_System PRIVATE 
    . 
    "${SFML_INCLUDE_DIR}"
)

# Library директории
target_link_directories(Solar_System PRIVATE "${SFML_LIB_DIR}")

# Линкуем статические библиотеки SFML
target_link_libraries(Solar_System
    sfml-system-s
    sfml-window-s
    sfml-graphics-s
    # sfml-audio-s  # Раскомментируйте если нужен audio
)

# Для статической сборки
target_compile_definitions(Solar_System PRIVATE SFML_STATIC)

# Обязательные системные библиотеки для Windows
if(WIN32)
    target_link_libraries(Solar_System
        opengl32
        winmm
        gdi32
        freetype
        # openal32    # Раскомментируйте если используете audio
    )
endif()

# Для Linux
if(UNIX AND NOT APPLE)
    find_package(X11 REQUIRED)
    target_link_libraries(Solar_System
        X11
        pthread
        # openal      # Раскомментируйте если используете audio
    )
endif()

# Копирование DLL файлов после сборки (для отладки)
if(WIN32 AND NOT SFML_STATIC_LIBRARIES)
    add_custom_command(TARGET Solar_System POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "${SFML_ROOT}/bin/openal32.dll"
        $<TARGET_FILE_DIR:Solar_System>
        COMMENT "Copying OpenAL DLL"
    )
endif()