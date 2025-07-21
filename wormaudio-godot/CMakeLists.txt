cmake_minimum_required(VERSION 3.22)

message(STATUS "Using CMake ${CMAKE_VERSION}")

# Require out-of-source builds
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)

if (EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in the source directory. Please use a build subdirectory.")
endif ()

# Add paths to modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

# Turn on link time optimization for everything
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE ON)

# Output compile commands to compile_commands.json (for debugging CMake issues)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Build universal lib on macOS
# Note that CMAKE_OSX_ARCHITECTURES must be set before project().
if (APPLE)
    set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64" CACHE STRING "")
endif ()

# Install the build plugin files to the project directory.
#
# NOTE: CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT SHOULD be true
# for "/usr/local", but for some reason it is not on my machine.
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT OR CMAKE_INSTALL_PREFIX STREQUAL "/usr/local")
    set_property(CACHE CMAKE_INSTALL_PREFIX PROPERTY VALUE "${CMAKE_SOURCE_DIR}/project/addons")
endif ()

# Main project information
project(wormaudio-godot
        LANGUAGES
            CXX
        VERSION
            0.1.0
)

# Create our library
add_library(${PROJECT_NAME} SHARED
        src/resource/WASystemResource.cpp
        src/resource/WASystemResource.hpp
        src/node/WAListenerNode.cpp
        src/node/WAListenerNode.hpp
        src/WARuntime.cpp
        src/WARuntime.hpp
        src/sound/WASoundDef.cpp
        src/sound/WASoundDef.hpp
        src/sound/WASoundInstance.cpp
        src/sound/WASoundInstance.hpp
        src/sound/WATransport.cpp
        src/sound/WATransport.hpp
)

target_compile_features(${PROJECT_NAME}
        PRIVATE
            cxx_std_20
)

# LIB_ARCH is the architecture being built. It is set to the build system's architecture.
# For macOS, we build a universal library (both arm64 and x86_64).
set(LIB_ARCH ${CMAKE_SYSTEM_PROCESSOR})
if (APPLE)
    set(LIB_ARCH "universal")
endif ()

# LIB_DIR is where the actual library ends up. This is used in both the build directory and the
# install directory and needs to be consistent with the paths in the gdextension file.
#   e.g. linux.release.x86_64 = "lib/Linux-x86_64/libGDExtensionTemplate.so"
set(LIB_DIR "lib/${CMAKE_SYSTEM_NAME}-${LIB_ARCH}")

message(STATUS "Building ${PROJECT_NAME} for ${LIB_ARCH} on ${CMAKE_SYSTEM_NAME}")

# BUILD_OUTPUT_DIR is where we put the resulting library (in the build directory)
set(BUILD_OUTPUT_DIR "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/")

set_target_properties(${PROJECT_NAME}
        PROPERTIES
            CXX_VISIBILITY_PRESET hidden
            VISIBILITY_INLINES_HIDDEN true
            RUNTIME_OUTPUT_DIRECTORY "${BUILD_OUTPUT_DIR}/${LIB_DIR}"
            LIBRARY_OUTPUT_DIRECTORY "${BUILD_OUTPUT_DIR}/${LIB_DIR}"
            INSTALL_RPATH "${CMAKE_INSTALL_RPATH};."
)

if (NOT DEFINED CMAKE_DEBUG_POSTFIX)
    set_target_properties(${PROJECT_NAME}
            PROPERTIES
                DEBUG_POSTFIX "-d"
    )
endif ()

# Copy over additional files from the support_files directory
add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/support_files"
            ${BUILD_OUTPUT_DIR}
)

# Warnings
include(CompilerWarnings)

# Create and include version info file from git
include(GitVersionInfo)

add_subdirectory(src)

# Install library, extension file, and support files in ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}
set(INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}/")

message(STATUS "Install directory: ${INSTALL_DIR}")

install(TARGETS ${PROJECT_NAME}
        LIBRARY
            DESTINATION ${INSTALL_DIR}/${LIB_DIR}
        RUNTIME
            DESTINATION ${INSTALL_DIR}/${LIB_DIR}
)

# Copy over support files
install(DIRECTORY "${CMAKE_SOURCE_DIR}/support_files/"
        DESTINATION ${INSTALL_DIR}
            PATTERN ".*" EXCLUDE
)

add_subdirectory(templates)

# ccache
# Turns on ccache if found
include(ccache)

# Formatting
# Adds a custom target to format all the code at once
include(ClangFormat)

# godot-cpp
# From here: https://github.com/godotengine/godot-cpp
if (NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/extern/godot-cpp/Makefile")
    message(
            FATAL_ERROR
                "[${PROJECT_NAME}] The godot-cpp submodule was not downloaded. Please update submodules: git submodule update --init --recursive."
    )
endif ()

set(GODOT_CPP_SYSTEM_HEADERS ON CACHE BOOL "" FORCE)

add_subdirectory(extern/godot-cpp)
add_subdirectory(../wormaudio player)

#set(SOURCE_FILES
#        src/Example.hpp
#        src/Example.cpp
#        src/GDExtensionTemplate.hpp
#        src/GDExtensionTemplate.cpp
#        src/RegisterExtension.cpp
#        src/WormAudioGodot.hpp
#        src/WormAudioGodot.cpp
#)

# I'LL JUST GLOB IT! WATCH ME GLOB THE FUCKING FILES. YOU CAN'T STOP ME!
# I'VE SPENT WEEKS OF PRECIOUS TIME CONFIGURING CMAKE
# SOMETHING AS SIMPLE AS RENAMING A PROJECT TAKES HALF THE DAY
# I HAVEN'T FIXED A SINGLE BUG IN WEEKS BECAUSE I'VE BEEN TOO BUSY RESTRUCTURING MY PROJECT
# BUT I KNOW I'LL HAVE TO DO IT ALL AGAIN WHEN THE NEW STRUCTURE INEVITABLY PROVES ARCHITECTURALLY UNSOUND
# I'LL GLOB THE FILES AND SAVE HOURS OF INANE TYPING
# I AM GOING INSANE
file(GLOB_RECURSE SOURCE_FILES
        CONFIGURE_DEPENDS
        "src/*.cpp"
        "src/*.hpp")

target_sources(${PROJECT_NAME}
        PRIVATE
            ${SOURCE_FILES}
)

set_target_properties(godot-cpp
        PROPERTIES
            CXX_VISIBILITY_PRESET hidden    # visibility needs to be the same as the main library
#            INSTALL_RPATH "${CMAKE_INSTALL_RPATH};./addons/lib/"
)

target_include_directories(${PROJECT_NAME}
        PUBLIC
        ../wormaudio
)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
            godot-cpp
        PUBLIC
            wormaudio
)

target_compile_definitions(${PROJECT_NAME}
        PRIVATE
            HOT_RELOAD_ENABLED=1
)

add_custom_target(install_${PROJECT_NAME}
        "${CMAKE_COMMAND}" --build "${CMAKE_BINARY_DIR}" --target install
            DEPENDS ${PROJECT_NAME}
            COMMENT "Installing ${PROJECT_NAME}")

add_executable(bootstrap_demo
        bootstrap_demo/bootstrap.cpp
)

target_include_directories(bootstrap_demo
        PRIVATE
        ../wormaudio/src
)

target_link_libraries(bootstrap_demo
        PRIVATE
            wormaudio
)