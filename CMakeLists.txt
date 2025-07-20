cmake_minimum_required(VERSION 3.22)
project(wormaudio-global VERSION 0.0.1)

add_subdirectory(wormaudio-editor)

add_custom_target(build_editor)
add_dependencies(build_editor
    wormaudio
    wormaudio-editor)

install(TARGETS wormaudio-editor
        DESTINATION ${CMAKE_INSTALL_DIR}/bin
)