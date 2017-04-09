set(SOURCE_FILES
		tgen.h tgen.cpp
		tgen_debug.h tgen_debug.cpp
		)

if(TGEN_STATIC_LIBRARY)
	add_library(tgen STATIC ${SOURCE_FILES})
else()
	add_library(tgen SHARED ${SOURCE_FILES})
endif()

install(TARGETS tgen
		RUNTIME DESTINATION bin
		ARCHIVE DESTINATION lib
		LIBRARY DESTINATION lib
		)

install(DIRECTORY . DESTINATION include
		FILES_MATCHING PATTERN "*.h"
)