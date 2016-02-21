cmake_minimum_required(VERSION 2.8)
find_package(GTest REQUIRED)

file(GLOB_RECURSE TESTS *.cpp)

foreach(TEST ${TESTS})
    get_filename_component(NAME ${TEST} NAME_WE)
    add_executable(${NAME} ${TEST})
    target_link_libraries(${NAME} ${GTEST_BOTH_LIBRARIES})
    target_include_directories(
        ${NAME}
        PUBLIC ${GTEST_INCLUDE_DIRS})
    add_test(NAME ${NAME} COMMAND ${NAME})
endforeach()
