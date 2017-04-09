set(SOURCE_FILES
		tgen.h tgen.cpp
		tgen_debug.h tgen_debug.cpp
		)

if(TGEN_SHARED_LIBRARY)
	add_library(tgen SHARED ${SOURCE_FILES})
else()
	add_library(tgen STATIC ${SOURCE_FILES})
endif()

if(EMSCRIPTEN)
	add_executable(tgen_driver EmscriptenMain.cpp)
else()
	add_executable(tgen_driver main.cpp)
endif()

target_link_libraries(tgen_driver PRIVATE tgen)
set_target_properties(tgen_driver PROPERTIES OUTPUT_NAME tgen)

install(TARGETS tgen_driver
		RUNTIME DESTINATION bin
)

install(TARGETS tgen
		RUNTIME DESTINATION bin
		ARCHIVE DESTINATION lib
		LIBRARY DESTINATION lib
		)

install(DIRECTORY . DESTINATION include
		FILES_MATCHING PATTERN "*.h"
)

if(EMSCRIPTEN)
	configure_file(webdemo.html index.html COPYONLY)
endif()