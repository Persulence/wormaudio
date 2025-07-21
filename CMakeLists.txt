cmake_minimum_required(VERSION 3.22)
project(wormaudio-global VERSION 0.0.1)

#if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT OR CMAKE_INSTALL_PREFIX STREQUAL "/usr/local")
#    set_property(CACHE CMAKE_INSTALL_PREFIX PROPERTY VALUE "${CMAKE_BINARY_DIR}/bin/install")
#endif()

if (DISABLE_WARNINGS)
    if (MSVC)
        string(REGEX REPLACE "/W[3|4]" "/w" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else ()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w")
    endif ()
endif ()

add_subdirectory(wormaudio-editor)

add_custom_target(build_editor)
add_dependencies(build_editor
        wormaudio
        wormaudio-editor)

install(TARGETS wormaudio-editor
)