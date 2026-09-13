cmake_minimum_required(VERSION 3.25)
project(FEmulator LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(JNI REQUIRED)

add_subdirectory(qemu)

add_library(femulator SHARED
    jni.cpp
)

set(SDL3_DIR "${CMAKE_CURRENT_SOURCE_DIR}/sdl/cmake")
find_package(SDL3 REQUIRED)

target_include_directories(femulator PRIVATE
    ${JNI_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/qemu/include
    ${CMAKE_CURRENT_SOURCE_DIR}/qemu
    ${SDL3_INCLUDE_DIRS}
)

target_link_libraries(femulator PRIVATE qemu)

if(WIN32)
    target_link_libraries(femulator PRIVATE
        WinHvPlatform user32 gdi32 ws2_32
        SDL3::SDL3
    )
endif()

if(UNIX AND NOT APPLE)
    add_compile_definitions(
        CONFIG_SDL=1
        CONFIG_SDL_VERSION=3
        CONFIG_VNC=1
        CONFIG_X11=1
    )
    target_link_libraries(femulator PRIVATE log SDL3::SDL3 X11)
endif()

target_compile_options(femulator PRIVATE -Os)