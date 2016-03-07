cmake_minimum_required(VERSION 2.8)
project(PSemu)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(functions)
setup_cmake_target()
run_feature_tests()

if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
	add_definitions(-fverbose-asm -g)
endif()


add_definitions(${FEATURE_LIST})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

enable_testing()

add_subdirectory(src)
add_subdirectory(deps)
add_subdirectory(tests)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
