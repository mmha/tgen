cmake_minimum_required(VERSION 3.4 FATAL_ERROR)
project(tgen)

set(CMAKE_CXX_STANDARD_REQUIRED 11)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

option(TGEN_STATIC_LIBRARY "Build tgen as a static library" OFF)

add_subdirectory(src bin)