set(JAVA_SWIG_TARGET ${LIBRARY_TARGET}-java)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_DEBUG} -fPIC")
# -fno-strict-aliasing is required by the SWIG documentation as generated code breaks aliasing rules
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fno-strict-aliasing -fPIC")

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
include_directories(..)

set_source_files_properties(../bindings.i PROPERTIES CPLUSPLUS ON)
# Causes the target to rebuild when an included header changes
set_source_files_properties(../bindings.i PROPERTIES USE_SWIG_DEPENDENCIES TRUE)

# Create dynamic native library
swig_add_library(${JAVA_SWIG_TARGET}
        SOURCES ../bindings.i
        LANGUAGE java
        OUTPUT_DIR ${SWIG_OUTPUT_DIR}
        OUTFILE_DIR .
)

# Remove stale files
# Doesn't fucking work because PRE_BUILD doesn't fucking work outside Microsoft Visual Studio
#add_custom_command(TARGET ${JAVA_SWIG_TARGET}
#        PRE_LINK
##            COMMAND rm ${SWIG_OUTPUT_DIR}/*.java || true
#            COMMAND echo --------------- deleting
#)
# I love having to manually organise the build folders

target_link_libraries(${JAVA_SWIG_TARGET}
        ${LIBRARY_TARGET}
        ${JNI_LIBRARIES}
)

get_property(thing TARGET ${JAVA_SWIG_TARGET} PROPERTY INCLUDE_DIRECTORIES)
message("include " ${thing})

set_property(TARGET ${JAVA_SWIG_TARGET} PROPERTY SWIG_USE_TARGET_INCLUDE_DIRECTORIES TRUE)
set_property(TARGET ${JAVA_SWIG_TARGET} PROPERTY LIBRARY_OUTPUT_DIRECTORY ${NEEPSOUND_OUTPUT_DIR})
set_property(TARGET ${JAVA_SWIG_TARGET} PROPERTY SWIG_COMPILE_OPTIONS -package ${JAVA_PACKAGE_NAME})
#set_property(TARGET ${JAVA_SWIG_TARGET} PROPERTY SWIG_USE_LIBRARY_INCLUDE_DIRECTORIES TRUE)

# Create Java library
get_property(some_java_sources TARGET ${JAVA_SWIG_TARGET} PROPERTY SWIG_SUPPORT_FILES)
get_property(java_source_dir TARGET ${JAVA_SWIG_TARGET} PROPERTY SWIG_SUPPORT_FILES_DIRECTORY)
#file(GLOB_RECURSE java_sources CONFIGURE_DEPENDS "${java_source_dir}/*")
message(STATUS "Non-exhaustive generated java sources: " ${some_java_sources})
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

set_property(TARGET ${JAR_NAME} PROPERTY EXCLUDE_FROM_ALL TRUE)

add_custom_command(TARGET ${JAVA_SWIG_TARGET}
        POST_BUILD
            # TODO: FOR TESTING
            COMMAND ${CMAKE_COMMAND} -E copy ${NEEPSOUND_OUTPUT_DIR}/libneepsound-java.so ${NEEPSOUND_OUTPUT_DIR}/../../../java_test/
            COMMAND ../../../compile_java.sh ${java_source_dir} ${NEEPSOUND_API_DIR}/java ${JAR_NAME}.jar
            COMMAND ${CMAKE_COMMAND} -E copy ${NEEPSOUND_API_DIR}/java/${JAR_NAME}.jar ${NEEPSOUND_OUTPUT_DIR}/../../../java_test/
)


#add_library(test_library)
#set_target_properties(test_library PROPERTIES LINKER_LANGUAGE CXX)
#target_include_directories(test_library
#        PUBLIC
#            ${JNI_INCLIDE_DIRS} .
#)
#target_sources(test_library PUBLIC java_alloc.hpp)