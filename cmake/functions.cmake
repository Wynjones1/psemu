macro(setup_local_gtest)
	set(GTEST_ROOT ${CMAKE_SOURCE_DIR}/deps/googletest)
	set(GTEST_LIBRARY gtest)
	set(GTEST_MAIN_LIBRARY gtest_main)
	set(GTEST_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/deps/googletest/include)

	find_package(GTest REQUIRED)
endmacro()

function(setup_cmake_target)
	file(GLOB SOURCES ${CMAKE_CURRENT_LIST_DIR}/*.cmake)
	add_custom_target(CMake SOURCES ${SOURCES})
	set_source_files_properties(${SOURCES} PROPERTIES HEADER_FILE_ONLY True)
	set_target_properties(CMake PROPERTIES FOLDER "CMake")
endfunction()

function(list_dir DIR VAR)
	file(GLOB TEMP ${DIR}/*)
	set(DIRS "")
	foreach(DIR ${TEMP})
		get_filename_component(FULL_PATH ${DIR} ABSOLUTE)
		if(IS_DIRECTORY ${FULL_PATH})
			list(APPEND DIRS ${FULL_PATH})
		endif()
	endforeach()
	set(${VAR} ${DIRS} PARENT_SCOPE)
endfunction()