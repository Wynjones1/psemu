cmake_minimum_required(VERSION 2.8)
include(functions)
setup_local_gtest()

file(GLOB_RECURSE TESTS *.cpp)

foreach(TEST ${TESTS})
    get_filename_component(NAME ${TEST} NAME_WE)
    add_executable(${NAME} ${TEST})
	set_property(TARGET ${NAME} PROPERTY CXX_STANDARD 11)
    target_link_libraries(${NAME} ${GTEST_BOTH_LIBRARIES} libpsemu)
    target_include_directories(
        ${NAME}
        PUBLIC ${GTEST_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/src)
    GTEST_ADD_TESTS(${NAME} "" ${TEST})
	set_target_properties(${NAME} PROPERTIES FOLDER "Tests")
endforeach()
