set(LIBRARY_TARGET wormaudio)

if (NOT MSVC)
    add_compile_options(-fPIC)
endif ()

cmake_minimum_required(VERSION 3.25)

project(PLAYER_LIBRARY VERSION 0.0.1)

# Causes problems (can't remember what problems), but we're not using modules anyway.
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

get_filename_component(WORMAUDIO_LIB_DIR ../lib ABSOLUTE CACHE)
set(WORMAUDIO_OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin CACHE INTERNAL "")
set(WORMAUDIO_API_DIR ${CMAKE_BINARY_DIR}/api CACHE INTERNAL "")

set(TARGET_OS ${CMAKE_SYSTEM_NAME} CACHE INTERNAL "")
string(TOLOWER ${TARGET_OS} TARGET_OS)
set(TARGET_ARCH amd64 CACHE INTERNAL "")
# Using an OS-independent extension '.slib'. This avoids parsing annoyance when locating the correct library.
# Java doesn't seem to see jar resources ending with .lib, so I've gone for a completely new shared library extension.
# (This might be because Windows uses .lib for static libraries)
set(WORMAUDIO_LIBRARY_SUFFIX "_${TARGET_OS}_${TARGET_ARCH}.slib" CACHE INTERNAL "")


# TODO: stop setting user variables
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${WORMAUDIO_OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${WORMAUDIO_OUTPUT_DIR})

# Hopefully prevent the millions of JUCE headers from appearing in the install dir.
# Linking to JUCE should bypass EXCLUDE_FROM_ALL for build.
add_subdirectory(${WORMAUDIO_LIB_DIR}/JUCE build EXCLUDE_FROM_ALL)

#set(UUID_SYSTEM_GENERATOR ON)
#add_subdirectory(${WORMAUDIO_LIB_DIR}/stduuid stduuid)

if (WORMAUDIO_BUILD_SWIG)
    add_subdirectory(swig EXCLUDE_FROM_ALL)
endif()

add_library(${LIBRARY_TARGET} STATIC)

set_target_properties(${LIBRARY_TARGET}
        PROPERTIES
            # Currently using a static library
#            SUFFIX "${WORMAUDIO_LIBRARY_SUFFIX}"
#            PREFIX ""

#            INSTALL_RPATH ${WORMAUDIO_OUTPUT_DIR} # ??????? Doesn't this hardcode the build dir? What is wrong with me?
            SKIP_BUILD_RPATH TRUE
            BUILD_WITH_INSTALL_RPATH TRUE
#            INSTALL_RPATH_USE_LINK_PATH TRUE
)

target_include_directories(${LIBRARY_TARGET}
        PUBLIC
            src
            SYSTEM ${WORMAUDIO_LIB_DIR}/cereal/include
            ${WORMAUDIO_LIB_DIR}/Cereal-Optional-NVP/include
#            ${WORMAUDIO_LIB_DIR}/stduuid/include/
        INTERFACE
            $<TARGET_PROPERTY:${LIBRARY_TARGET},INCLUDE_DIRECTORIES>

)

# Not using C++20 modules anymore
#file(GLOB_RECURSE ModuleFiles
#        CONFIGURE_DEPENDS
#        "src/*.ixx")

file(GLOB_RECURSE SourceFiles
        CONFIGURE_DEPENDS
        "src/*.cpp"
        "src/*.h")

target_sources("${LIBRARY_TARGET}"
#        PUBLIC
#            FILE_SET CXX_MODULES
#            FILES
#            ${ModuleFiles}
        PRIVATE
            ${SourceFiles}
            src/runtime/Runtime.cpp
        src/api/MessageThreadManager.hpp
)

set_property(TARGET ${LIBRARY_TARGET} PROPERTY CXX_STANDARD 20)

target_compile_features(${LIBRARY_TARGET}
    PUBLIC
    cxx_std_20)

target_compile_definitions(${LIBRARY_TARGET}
        PUBLIC
#            UUID_SYSTEM_GENERATOR=ON
            # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
            JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_gui_app` call
            JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_gui_app` call
            JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:${LIBRARY_TARGET},JUCE_PRODUCT_NAME>"
            JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:${LIBRARY_TARGET},JUCE_VERSION>"
            JUCE_DISABLE_JUCE_VERSION_PRINTING=1 # Not necessary and causes a segfault when loaded by Godot
        INTERFACE
            $<TARGET_PROPERTY:${LIBRARY_TARGET},COMPILE_DEFINITIONS>
)


target_link_libraries(${LIBRARY_TARGET}
        PRIVATE
#        PUBLIC
        juce::juce_audio_devices
        juce::juce_audio_formats
#        juce::juce_audio_processors
#        juce::juce_audio_utils
        juce::juce_core
#        juce::juce_data_structures
#        juce::juce_events
#        juce::juce_graphics
        juce::juce_gui_basics
        juce::juce_opengl
#        juce::juce_gui_extra
        juce::juce_audio_basics
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
#        juce::juce_recommended_warning_flags
#        stduuid
)

file(GLOB_RECURSE JUCE_SOURCES CONFIGURE_DEPENDS ${WORMAUDIO_LIB_DIR}/JUCE/*.cpp  ${WORMAUDIO_LIB_DIR}/JUCE/*.mm ${WORMAUDIO_LIB_DIR}/JUCE/*.r)
set_source_files_properties(${JUCE_SOURCES} PROPERTIES SKIP_PRECOMPILE_HEADERS TRUE SKIP_UNITY_BUILD_INCLUSION TRUE)

file(GLOB_RECURSE CEREAL_HEADERS CONFIGURE_DEPENDS ${WORMAUDIO_LIB_DIR}/cereal/*)
set_source_files_properties(${CEREAL_HEADERS} PROPERTIES SKIP_UNITY_BUILD_INCLUSION TRUE)

# JUCE modules use their own unity build configuration. Including them in the automatic Cmake unity build causes issues.
set_source_files_properties(
        src/resource/serialization.hpp
        src/resource/ClipElement.cpp
        src/resource/ChoiceElement.cpp
        PROPERTIES SKIP_UNITY_BUILD_INCLUSION TRUE)

# Precompiled headers seemed to actually increase build time.
# Not sure what I did wrong.
#target_precompile_headers(${LIBRARY_TARGET}
#    PRIVATE
#        "$<$<COMPILE_LANGUAGE:CXX>:vector>"
#        "$<$<COMPILE_LANGUAGE:CXX>:algorithm>"
#        "$<$<COMPILE_LANGUAGE:CXX>:ranges>"
#        "$<$<COMPILE_LANGUAGE:CXX>:memory>"
#        "$<$<COMPILE_LANGUAGE:CXX>:string>"
#        "$<$<COMPILE_LANGUAGE:CXX>:cmath>"
#        "$<$<COMPILE_LANGUAGE:CXX>:iostream>"
#        "$<$<COMPILE_LANGUAGE:CXX>:variant>"
#        "$<$<COMPILE_LANGUAGE:CXX>:utility>"
#
##        "$<$<COMPILE_LANGUAGE:CXX>:juce_gui_basics/juce_gui_basics.h>"
#        "$<$<COMPILE_LANGUAGE:CXX>:juce_audio_basics/juce_audio_basics.h>"
#        "$<$<COMPILE_LANGUAGE:CXX>:juce_core/juce_core.h>"
#        "$<$<COMPILE_LANGUAGE:CXX>:juce_data_structures/juce_data_structures.h>"
#        "$<$<COMPILE_LANGUAGE:CXX>:juce_audio_devices/juce_audio_devices.h>"
#        "$<$<COMPILE_LANGUAGE:CXX>:JuceHeader.h>"
#    )

#install(TARGETS ${LIBRARY_TARGET}
#)

# It is not recommended to enable unity build in CMakeLists.txt, but I was having trouble getting it to work.
set_target_properties(${LIBRARY_TARGET} PROPERTIES
#        UNITY_BUILD ON
        UNITY_BUILD_MODE BATCH
        UNITY_BUILD_BATCH_SIZE 10
)

#if (${WORMAUDIO_BUILD_SWIG})
#    add_custom_target(build_swig1)
#    add_dependencies(build_swig1
#            wormaudio
#            wormaudio-java
#    )
#endif ()
