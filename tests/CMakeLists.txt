cmake_minimum_required(VERSION 3.8)

project(testsuite)

add_executable(	testsuite main.cpp)

target_link_libraries(testsuite
	PUBLIC
		gtest_main
		gmock_main
		pslog
)

add_test(NAME testsuite_test COMMAND testsuite)
