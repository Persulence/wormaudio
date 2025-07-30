set(GUI_TARGET wormaudio-editor)

# TODO: should not be set here
set(CMAKE_CXX_FLAGS_DEBUG
        "${CMAKE_CXX_FLAGS} -fsanitize=undefined,address"
)

cmake_minimum_required(VERSION 3.25)

project(GUI_APP_EXAMPLE VERSION 0.0.1)

# Causes problems (can't remember what problems), but we're not using modules anyway.
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

add_subdirectory(../wormaudio wormaudio)

# Works with modules
# TODO: Ensure that necessary JUCE properties are also set
if (MSVC)
    add_executable(${GUI_TARGET} WIN32 src/Main.cpp)
else ()
    add_executable(${GUI_TARGET}
            src/Version.hpp
            src/editor/EditorState.cpp
            src/editor/EditorState.hpp)
endif ()

#target_precompile_headers(${GUI_TARGET}
#        INTERFACE
#                juce_basics/juce_basics.h
#)

target_include_directories(${GUI_TARGET}
        PUBLIC
        ../wormaudio/src
        src
#            lib/JUCE/modules
)

#include(CMakePrintHelpers)
#cmake_print_properties(TARGETS ${GUI_TARGET} PROPERTIES INCLUDE_DIRECTORIES)

#file(GLOB_RECURSE ModuleFiles
#        CONFIGURE_DEPENDS
#        "src/*.ixx")

file(GLOB_RECURSE SourceFiles
        CONFIGURE_DEPENDS
        "src/*.cpp"
        "src/*.h")

target_sources("${GUI_TARGET}"
#        PUBLIC
#            FILE_SET CXX_MODULES
#            FILES
#            ${ModuleFiles}
        PRIVATE
            ${SourceFiles})

set_property(TARGET ${GUI_TARGET} PROPERTY CXX_STANDARD 20)

target_compile_features(${GUI_TARGET}
    PUBLIC
    cxx_std_20)

target_compile_definitions(${GUI_TARGET}
        PRIVATE
        # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_gui_app` call
        JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_gui_app` call
        JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:${GUI_TARGET},JUCE_PRODUCT_NAME>"
        JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:${GUI_TARGET},JUCE_VERSION>")

target_link_libraries(${GUI_TARGET}
        PRIVATE
#        juce::juce_audio_basics
#        juce::juce_audio_devices
#        juce::juce_audio_formats
#        juce::juce_audio_processors
#        juce::juce_audio_utils
#        juce::juce_core
#        juce::juce_data_structures
#        juce::juce_events
#        juce::juce_graphics
#        juce::juce_gui_basics
#        juce::juce_gui_extra
#        juce::juce_opengl
        PUBLIC
        wormaudio
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
#        juce::juce_recommended_warning_flags
)

file(GLOB_RECURSE JUCE_SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/lib/JUCE/*.cpp  ${CMAKE_SOURCE_DIR}/lib/JUCE/*.mm ${CMAKE_SOURCE_DIR}/lib/JUCE/*.r)
set_source_files_properties(${JUCE_SOURCES} PROPERTIES SKIP_PRECOMPILE_HEADERS TRUE SKIP_UNITY_BUILD_INCLUSION TRUE)

file(GLOB_RECURSE CEREAL_HEADERS CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/lib/cereal/*)
set_source_files_properties(${CEREAL_HEADERS} PROPERTIES SKIP_UNITY_BUILD_INCLUSION TRUE)

#set_source_files_properties(
#        src/Main.cpp
#        PROPERTIES SKIP_UNITY_BUILD_INCLUSION TRUE)

#target_precompile_headers(${GUI_TARGET}
#        PRIVATE
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
#        # PCH is not supported by JUCE. Yay. Wish I'd know that earlier.
#        "$<$<COMPILE_LANGUAGE:CXX>:juce_gui_basics/juce_gui_basics.h>"
#        "$<$<COMPILE_LANGUAGE:CXX>:juce_audio_basics/juce_audio_basics.h>"
#        "$<$<COMPILE_LANGUAGE:CXX>:juce_core/juce_core.h>"
#        "$<$<COMPILE_LANGUAGE:CXX>:juce_data_structures/juce_data_structures.h>"
#        "$<$<COMPILE_LANGUAGE:CXX>:juce_audio_devices/juce_audio_devices.h>"
#        "$<$<COMPILE_LANGUAGE:CXX>:JuceHeader.h>"
#)

#set_target_properties(${GUI_TARGET} PROPERTIES UNITY_BUILD ON)
# It is not recommended to enable unity build here, but I was having trouble getting it to work.
set_target_properties(${GUI_TARGET} PROPERTIES
#        UNITY_BUILD ON
        UNITY_BUILD_MODE BATCH
        UNITY_BUILD_BATCH_SIZE 10
)

install(TARGETS wormaudio-editor)

install(DIRECTORY res
        DESTINATION .)

message(STATUS "Editor install prefix: ${CMAKE_INSTALL_PREFIX}")