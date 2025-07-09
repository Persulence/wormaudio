set(JAVA_SWIG_TARGET ${LIBRARY_TARGET}-java)
#message("output java: " ${LIBRARY_OUTPUT_DIRECTORY})

find_package(JNI REQUIRED)
include_directories(${JNI_INCLUDE_DIRS})
message("Using JNI includes at: " ${JNI_INCLUDE_DIRS})


set(CMAKE_SWIG_FLAGS "")
set_source_files_properties(../bindings.i PROPERTIES CPLUSPLUS ON)
include_directories(..)

# Add swig module
swig_add_library(${JAVA_SWIG_TARGET}
        SOURCES ../bindings.i
        LANGUAGE java
#        OUTPUT_DIR ${API_OUTPUT_DIR}/java
        OUTPUT_DIR ../../api/java
        OUTFILE_DIR .
)
swig_link_libraries(${JAVA_SWIG_TARGET} ${LIBRARY_TARGET} ${JNI_LIBRARIES})

set_target_properties(${JAVA_SWIG_TARGET} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${NEEPSOUND_OUTPUT_DIR})
