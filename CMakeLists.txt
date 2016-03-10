cmake_minimum_required(VERSION 2.8)
project(PSemu)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(functions)
cmake_setup()
setup_cmake_target()
run_feature_tests()

option(COVERAGE_ON "Enable code coverage (if available)" True)

if(IS_CLANG OR IS_GCC)
	add_definitions(-fverbose-asm -g)
    if(COVERAGE_ON)
        add_definitions(--coverage -fprofile-arcs -ftest-coverage)
        #if(IS_GCC)
        #    add_definitions(-fprofile-dir=${CMAKE_BINARY_DIR}/coverage)
        #endif()
    endif()
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
