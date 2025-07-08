set(JAVA_SWIG_TARGET ${LIBRARY_TARGET}-java)

find_package(JNI REQUIRED)
include_directories(${JNI_INCLUDE_DIRS})


set(CMAKE_SWIG_FLAGS "")
set_source_files_properties(../bindings.i PROPERTIES CPLUSPLUS ON)
include_directories(..)

# Add swig module
swig_add_library(${JAVA_SWIG_TARGET}
        SOURCES ../bindings.i
        LANGUAGE java
)
swig_link_libraries(${JAVA_SWIG_TARGET} ${LIBRARY_TARGET} ${JNI_LIBRARIES})
