set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
# -fno-strict-aliasing is required by the SWIG documentation as generated code breaks aliasing rules
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fno-strict-aliasing -fPIC") # TODO: change to add_compile_options
set(CMAKE_INSTALL_RPATH "")

set(JAVA_SWIG_TARGET ${LIBRARY_TARGET}-java)
set(JAVA_PACKAGE_NAME "com.wormaudio.wormaudio.generated")
set(SWIG_OUTPUT_DIR "${WORMAUDIO_API_DIR}/java/com/wormaudio/wormaudio/generated")
set(JAR_NAME "NEEPSound")


find_package(Java 17 REQUIRED)
message(STATUS "Found Java version: " ${Java_VERSION})
include(UseJava) # Necessary unlike UseSwig

find_package(JNI REQUIRED)
include_directories(${JNI_INCLUDE_DIRS})
message(STATUS "Using JNI includes at: " ${JNI_INCLUDE_DIRS})


set(CMAKE_SWIG_FLAGS "")
include_directories(..)

set_source_files_properties(../main.i PROPERTIES CPLUSPLUS ON)
# Causes the target to rebuild when an included header changes
set_source_files_properties(../main.i PROPERTIES USE_SWIG_DEPENDENCIES TRUE)

# Create dynamic native library
swig_add_library(${JAVA_SWIG_TARGET}
        TYPE SHARED
        SOURCES ../main.i
        LANGUAGE java
        OUTPUT_DIR ${SWIG_OUTPUT_DIR}
        OUTFILE_DIR .
)

set_target_properties(${JAVA_SWIG_TARGET}
        PROPERTIES
            SUFFIX "${WORMAUDIO_LIBRARY_SUFFIX}"
            PREFIX ""
)

# Remove stale files
# Doesn't fucking work because PRE_BUILD doesn't fucking work outside Microsoft Visual Studio
#add_custom_command(TARGET ${JAVA_SWIG_TARGET}
#        PRE_LINK
##            COMMAND rm ${SWIG_OUTPUT_DIR}/*.java || true
#            COMMAND echo --------------- deleting
#)
# I love having to manually organise the build folders

target_sources(${JAVA_SWIG_TARGET}
        PRIVATE
            ../bindings.cpp
            ../runtime.b.cpp
            message.b.cpp
            logger.b.cpp
)

target_link_libraries(${JAVA_SWIG_TARGET}
        ${LIBRARY_TARGET}
        ${JNI_LIBRARIES}
)

get_property(thing TARGET ${JAVA_SWIG_TARGET} PROPERTY INCLUDE_DIRECTORIES)
#message(STATUS "include " ${thing})

set_property(TARGET ${JAVA_SWIG_TARGET} PROPERTY SWIG_USE_TARGET_INCLUDE_DIRECTORIES TRUE)
#set_property(TARGET ${JAVA_SWIG_TARGET} PROPERTY LIBRARY_OUTPUT_DIRECTORY ${WORMAUDIO_OUTPUT_DIR})
set_property(TARGET ${JAVA_SWIG_TARGET} PROPERTY SWIG_COMPILE_OPTIONS -package ${JAVA_PACKAGE_NAME})
#set_property(TARGET ${JAVA_SWIG_TARGET} PROPERTY SWIG_COMPILE_OPTIONS -package ${JAVA_PACKAGE_NAME} -noproxy)

# Create Java library
get_property(some_java_sources TARGET ${JAVA_SWIG_TARGET} PROPERTY SWIG_SUPPORT_FILES)
get_property(java_source_dir TARGET ${JAVA_SWIG_TARGET} PROPERTY SWIG_SUPPORT_FILES_DIRECTORY)
#file(GLOB_RECURSE java_sources CONFIGURE_DEPENDS "${java_source_dir}/*")
message(STATUS "Non-exhaustive generated java sources: " ${some_java_sources})
message(STATUS "Java source dir: " ${java_source_dir})
#message(STATUS "Generated java sources: " ${java_sources})

#add_jar(${JAR_NAME}
#        SOURCES
##            ${java_sources}
#        # TODO: Find a way to grab the generated sources and automatically add them here
#            ${java_source_dir}/NEEPSound.java
#            ${java_source_dir}/NEEPSoundJNI.java
#            ${java_source_dir}/SoundThing.java
#        OUTPUT_DIR ${WORMAUDIO_API_DIR}/java
#)
#add_dependencies(${JAR_NAME} ${JAVA_SWIG_TARGET})
#set_property(TARGET ${JAR_NAME} PROPERTY EXCLUDE_FROM_ALL TRUE)

#install(TARGETS ${JAVA_SWIG_TARGET}
#        DESTINATION ${WORMAUDIO_OUTPUT_DIR}
#)

add_custom_command(TARGET ${JAVA_SWIG_TARGET}
        POST_BUILD
            # TODO: FOR TESTING
            COMMAND cp ${WORMAUDIO_OUTPUT_DIR}/*.slib ${WORMAUDIO_OUTPUT_DIR}/../../../wormaudio-java/src/main/resources/native/ # TODO
#            COMMAND ../../../compile_java.sh ${java_source_dir} ${WORMAUDIO_API_DIR}/java ${JAR_NAME}.jar
#            COMMAND ${CMAKE_COMMAND} -E copy ${WORMAUDIO_API_DIR}/java/${JAR_NAME}.jar ${WORMAUDIO_OUTPUT_DIR}/../../../java_test/
            COMMAND cp -r ${java_source_dir}/*.java ${WORMAUDIO_OUTPUT_DIR}/../../../wormaudio-java/src/main/java/com/wormaudio/wormaudio/generated
)

add_executable(test_exec test_exec.cpp)
target_link_libraries(test_exec PUBLIC ${JAVA_SWIG_TARGET})

#add_library(test_library)
#set_target_properties(test_library PROPERTIES LINKER_LANGUAGE CXX)
#target_include_directories(test_library
#        PUBLIC
#            ${JNI_INCLIDE_DIRS} .
#)
#target_sources(test_library PUBLIC java_alloc.hpp)
