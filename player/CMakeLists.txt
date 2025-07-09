# Example GUI App CMakeLists.txt

# To get started on a new GUI app, copy this entire folder (containing this file and C++ sources) to
# a convenient location, and then start making modifications. For other examples of CMakeLists for
# GUI apps, check `extras/Projucer` and `examples/DemoRunner` in the JUCE repo.

# The first line of any CMake project should be a call to `cmake_minimum_required`, which checks
# that the installed CMake will be able to understand the following CMakeLists, and ensures that
# CMake's behaviour is compatible with the named version. This is a standard CMake command, so more
# information can be found in the CMake docs.

set(LIB_DIR ../lib)

set(LIBRARY_TARGET neepsound)
set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_COMPILER /usr/bin/g++-15)
set(CMAKE_CXX_COMPILER /usr/bin/g++)
#set(CMAKE_GENERATOR Ninja)

cmake_minimum_required(VERSION 4.0)

# The top-level CMakeLists.txt file for a project must contain a literal, direct call to the
# `project()` command. `project()` sets up some helpful variables that describe source/binary
# directories, and the current project version. This is a standard CMake command.

project(PLAYER_LIBRARY VERSION 0.0.1)

set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

# If you've installed JUCE somehow (via a package manager, or directly using the CMake install
# target), you'll need to tell this project that it depends on the installed copy of JUCE. If you've
# included JUCE directly in your source tree (perhaps as a submodule), you'll need to tell CMake to
# include that subdirectory as part of the build.

#find_package(JUCE CONFIG REQUIRED)        # If you've installed JUCE to your system

add_subdirectory(${LIB_DIR}/JUCE build)

#add_subdirectory(src/swig)
add_subdirectory(swig)

set(NEEPSOUND_OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin CACHE INTERNAL "")
set(NEEPSOUND_API_DIR ${CMAKE_BINARY_DIR}/api CACHE INTERNAL "")
message(STATUS "Binary outputs will be found in: " ${NEEPSOUND_OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${NEEPSOUND_OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY  ${NEEPSOUND_OUTPUT_DIR})
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./lib)

# This command sets cxx_std_17 somewhere. We're using C++20, so this can't be used.
#juce_add_gui_app(${LIBRARY_TARGET}
#        # VERSION ...                       # Set this if the app version is different to the project version
#        # ICON_BIG ...                      # ICON_* arguments specify a path to an image file to use as an icon
#        # ICON_SMALL ...
#        # DOCUMENT_EXTENSIONS ...           # Specify file extensions that should be associated with this app
#        # COMPANY_NAME ...                  # Specify the name of the app's author
#        PRODUCT_NAME "Gui App Example")     # The name of the final executable, which can differ from the target name

# TODO: Ensure that necessary JUCE properties are also set
add_library(${LIBRARY_TARGET} STATIC)

# `juce_generate_juce_header` will create a JuceHeader.h for a given target, which will be generated
# into your build tree. This should be included with `#include <JuceHeader.h>`. The include path for
# this header will be automatically added to the target. The main function of the JuceHeader is to
# include all your JUCE module headers; if you're happy to include module headers directly, you
# probably don't need to call this.

# juce_generate_juce_header(${LIBRARY_TARGET})

target_include_directories(${LIBRARY_TARGET}
        PUBLIC
            ../JuceLibraryCode
            src
            SYSTEM ${LIB_DIR}/cereal/include
            ${LIB_DIR}/Cereal-Optional-NVP/include

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
            ${SourceFiles})

set_property(TARGET ${LIBRARY_TARGET} PROPERTY CXX_STANDARD 20)

target_compile_features(${LIBRARY_TARGET}
    PUBLIC
    cxx_std_20)

# `target_compile_definitions` adds some preprocessor definitions to our target. In a Projucer
# project, these might be passed in the 'Preprocessor Definitions' field. JUCE modules also make use
# of compile definitions to switch certain features on/off, so if there's a particular feature you
# need that's not on by default, check the module header for the correct flag to set here. These
# definitions will be visible both to your code, and also the JUCE module code, so for new
# definitions, pick unique names that are unlikely to collide! This is a standard CMake command.

target_compile_definitions(${LIBRARY_TARGET}
        PRIVATE
        # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_gui_app` call
        JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_gui_app` call
        JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:${LIBRARY_TARGET},JUCE_PRODUCT_NAME>"
        JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:${LIBRARY_TARGET},JUCE_VERSION>")


# If your target needs extra binary assets, you can add them here. The first argument is the name of
# a new static library target that will include all the binary resources. There is an optional
# `NAMESPACE` argument that can specify the namespace of the generated binary data class. Finally,
# the SOURCES argument should be followed by a list of source files that should be built into the
# static library. These source files can be of any kind (wav data, images, fonts, icons etc.).
# Conversion to binary-data will happen when your target is built.

# juce_add_binary_data(GuiAppData SOURCES ...)

# `target_link_libraries` links libraries and JUCE modules to other libraries or executables. Here,
# we're linking our executable target to the `juce::juce_gui_extra` module. Inter-module
# dependencies are resolved automatically, so `juce_core`, `juce_events` and so on will also be
# linked automatically. If we'd generated a binary data target above, we would need to link to it
# here too. This is a standard CMake command.

#target_link_libraries(${LIBRARY_TARGET}
target_link_libraries(${LIBRARY_TARGET}
        PRIVATE
        # GuiAppData            # If we'd created a binary data target, we'd link to it here
        juce::juce_audio_basics
#        juce::juce_audio_devices
#        juce::juce_audio_formats
#        juce::juce_audio_processors
        juce::juce_audio_utils
        juce::juce_core
#        juce::juce_data_structures
#        juce::juce_events
#        juce::juce_graphics
        juce::juce_gui_basics
#        juce::juce_gui_extra
        PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)

file(GLOB_RECURSE JUCE_SOURCES CONFIGURE_DEPENDS ${LIB_DIR}/JUCE/*.cpp  ${LIB_DIR}/JUCE/*.mm ${LIB_DIR}/JUCE/*.r)
set_source_files_properties(${JUCE_SOURCES} PROPERTIES SKIP_PRECOMPILE_HEADERS TRUE SKIP_UNITY_BUILD_INCLUSION TRUE)

file(GLOB_RECURSE CEREAL_HEADERS CONFIGURE_DEPENDS ${LIB_DIR}/cereal/*)
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

# It is not recommended to enable unity build in CMakeLists.txt, but I was having trouble getting it to work.
#set_property(TARGET ${LIBRARY_TARGET} PROPERTY UNITY_BUILD ON)
set_target_properties(${LIBRARY_TARGET} PROPERTIES
        UNITY_BUILD ON
        UNITY_BUILD_MODE BATCH
        UNITY_BUILD_BATCH_SIZE 10
)
