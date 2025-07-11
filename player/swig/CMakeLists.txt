find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})

message(STATUS "Found SWIG: " ${SWIG_EXECUTABLE})

option(BUILD_JAVA "Build Java SWIG module" ON)
if(BUILD_JAVA)
    add_subdirectory(java)
endif()

#add_executable(exec exec_test.cpp)
#target_link_libraries(exec PUBLIC ${LIBRARY_TARGET})