cmake_minimum_required(VERSION 3.4 FATAL_ERROR)
project(tgen)

set(CMAKE_CXX_STANDARD_REQUIRED 11)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

if(EMSCRIPTEN)
	option(TGEN_WEBASSEMBLY "Generate WebAssembly instead of asm.js" OFF)
	if(TGEN_WEBASSEMBLY)
		set(CMAKE_CXX_FLAGS "-s WASM=1 ${CMAKE_CXX_FLAGS}")
	endif()

	# For some reason CMAKE_CXX_STANDARD_REQUIRED does not work for emscripten
	set(CMAKE_CXX_FLAGS  "--bind -std=c++11 ${CMAKE_CXX_FLAGS}")
else()
	option(TGEN_SHARED_LIBRARY "Build tgen as a shared library" OFF)
endif()

add_subdirectory(src bin)