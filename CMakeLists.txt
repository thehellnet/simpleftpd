cmake_minimum_required(VERSION 3.1)

project(simpleftpd)

enable_language(C)
enable_testing()

if (CMAKE_SYSTEM_NAME STREQUAL Android)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIE")
endif ()

add_subdirectory(src)
