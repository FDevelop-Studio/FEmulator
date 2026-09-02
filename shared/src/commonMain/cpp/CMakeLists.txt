cmake_minimum_required(VERSION 3.25)
project(FEmulator LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(JNI REQUIRED)

add_subdirectory(qemu/qemu-11.1.0)

add_library(femulator SHARED
    jni.cpp
)

target_include_directories(femulator PRIVATE
    ${JNI_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/qemu/qemu-11.1.0/include
)

target_link_libraries(femulator PRIVATE qemu)

if(WIN32)
    target_link_libraries(femulator PRIVATE WinHvPlatform user32 gdi32 ws2_32)
endif()

target_compile_options(femulator PRIVATE -Os)