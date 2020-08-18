cmake_minimum_required(VERSION 3.8)

project(example)

add_executable(	example main.cpp)

target_link_libraries(example
	PUBLIC
		gtest_main
		pslog
)

add_test(NAME example_test COMMAND example)
