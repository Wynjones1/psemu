cmake_minimum_required(VERSION 2.8)

if(WIN32)
	option(gtest_force_shared_crt "" On)
endif()

add_subdirectory(googletest)
set_target_properties(gmock      PROPERTIES FOLDER "gtest")
set_target_properties(gmock_main PROPERTIES FOLDER "gtest")
set_target_properties(gtest      PROPERTIES FOLDER "gtest")
set_target_properties(gtest_main PROPERTIES FOLDER "gtest")