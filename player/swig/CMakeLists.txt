find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})

message("Found SWIG: " ${SWIG_EXECUTABLE})

option(BUILD_JAVA "Build Java SWIG module" ON)
if(BUILD_JAVA)
    add_subdirectory(java)
endif()
