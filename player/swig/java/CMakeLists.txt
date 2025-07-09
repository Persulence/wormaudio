set(JAVA_SWIG_TARGET ${LIBRARY_TARGET}-java)

# -fno-strict-aliasing is required by the SWIG documentation as generated code breaks aliasing rules
set(CMAKE_CXX_FLAGS_RELEASE  ${CMAKE_CXX_FLAGS_RELEASE} " -fno-strict-aliasing")

set(JAVA_PACKAGE_NAME "com.neep.neepsound")
set(SWIG_OUTPUT_DIR "${NEEPSOUND_API_DIR}/java/com/neep/neepsound")
set(JAR_NAME "NEEPSound")

find_package(JNI REQUIRED)
include_directories(${JNI_INCLUDE_DIRS})
message(STATUS "Using JNI includes at: " ${JNI_INCLUDE_DIRS})

find_package(Java REQUIRED)
message(STATUS "Found Java version: " ${Java_VERSION})
include(UseJava) # Necessary unlike UseSwig


set(CMAKE_SWIG_FLAGS "")
set_source_files_properties(../bindings.i PROPERTIES CPLUSPLUS ON)
include_directories(..)

# Create dynamic native library
swig_add_library(${JAVA_SWIG_TARGET}
        SOURCES ../bindings.i
        LANGUAGE java
        OUTPUT_DIR ${SWIG_OUTPUT_DIR}
#        OUTPUT_DIR ../../../../java_test/src/main/java/com/neep/neepsound # TODO: FOR TESTING
        OUTFILE_DIR .
)

target_link_libraries(${JAVA_SWIG_TARGET}
        ${LIBRARY_TARGET}
        ${JNI_LIBRARIES}
        ${JAVA_LIBRARIES}
)

set_property(TARGET ${JAVA_SWIG_TARGET} PROPERTY LIBRARY_OUTPUT_DIRECTORY ${NEEPSOUND_OUTPUT_DIR})
set_property(TARGET ${JAVA_SWIG_TARGET} PROPERTY SWIG_COMPILE_OPTIONS -package ${JAVA_PACKAGE_NAME})

# Create Java library
get_property(java_source_dir TARGET ${JAVA_SWIG_TARGET} PROPERTY SWIG_SUPPORT_FILES_DIRECTORY)
#file(GLOB_RECURSE java_sources CONFIGURE_DEPENDS "${java_source_dir}/*")
message(STATUS "Java source dir: " ${java_source_dir})
#message(STATUS "Generated java sources: " ${java_sources})
add_jar(${JAR_NAME}
        SOURCES
#            ${java_sources}
        # TODO: Find a way to grab the generated sources and automatically add them here
            ${java_source_dir}/NEEPSound.java
            ${java_source_dir}/NEEPSoundJNI.java
            ${java_source_dir}/SoundThing.java
        OUTPUT_DIR ${NEEPSOUND_API_DIR}/java
)

add_dependencies(${JAR_NAME} ${JAVA_SWIG_TARGET})

# TODO: FOR TESTING
add_custom_command(TARGET ${JAVA_SWIG_TARGET}
        POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${NEEPSOUND_OUTPUT_DIR}/libneepsound-java.so ${NEEPSOUND_OUTPUT_DIR}/../../../java_test/
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${NEEPSOUND_API_DIR}/java/${JAR_NAME}.jar ${NEEPSOUND_OUTPUT_DIR}/../../../java_test/
)
