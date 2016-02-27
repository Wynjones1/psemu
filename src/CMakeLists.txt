cmake_minimum_required(VERSION 2.8)

file(GLOB_RECURSE SOURCES *.cpp)
file(GLOB_RECURSE HEADERS *.h)
list(REMOVE_ITEM SOURCES main.cpp)

add_library(libpsemu ${SOURCES} ${HEADERS})
add_executable(psemu main.cpp)
target_link_libraries(psemu libpsemu)
set_property(TARGET psemu PROPERTY CXX_STANDARD 11)
set_property(TARGET libpsemu PROPERTY CXX_STANDARD 11)
set_target_properties(psemu PROPERTIES FOLDER "PSemu")
set_target_properties(libpsemu PROPERTIES FOLDER "PSemu")