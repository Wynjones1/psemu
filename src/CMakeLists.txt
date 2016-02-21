cmake_minimum_required(VERSION 2.8)

file(GLOB_RECURSE SOURCES *.cpp)
file(GLOB_RECURSE HEADERS *.h)

add_executable(psemu ${SOURCES} ${HEADERS})
set_property(TARGET psemu PROPERTY CXX_STANDARD 11)
