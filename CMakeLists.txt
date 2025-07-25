cmake_minimum_required(VERSION 3.22)
project(wormaudio-global VERSION 0.0.1)

if (DISABLE_WARNINGS)
    if (MSVC)
        message(STATUS "Attempting to disable MSVC warnings")
        string(REGEX REPLACE "/W[3|4]" "/w" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w /W0")
    else ()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w")
    endif ()
endif ()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

include(ccache)

add_subdirectory(wormaudio-editor)

add_custom_target(build_editor)
add_dependencies(build_editor
        wormaudio
        wormaudio-editor)

install(TARGETS wormaudio-editor)

if (${WORMAUDIO_BUILD_SWIG})
    add_custom_target(build_swig)
    add_dependencies(build_swig
            wormaudio
            wormaudio-java
    )
endif ()
