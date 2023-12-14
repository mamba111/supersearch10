cmake_minimum_required(VERSION 3.15)
project(FinalProjExamples)

# filesystem.h require C++17
set(CMAKE_CXX_STANDARD 17)

file(COPY sample_data/ DESTINATION sample_data/)

# show compiler output and enable warnings
set(CMAKE_VERBOSE_MAKEFILE ON)
add_compile_options(-Wall -Wextra -pedantic)

# Main executable
add_executable(supersearch main.cpp)

# Test executable for AVL Tree
add_executable(tests_AVL_Tree avl_tree_tests.cpp avl_tree_map.h)
add_test(NAME TestAVLTree COMMAND avl_tree_tests)


# this makes sure we also link rapidjson

set(CMAKE_VERBOSE_MAKEFILE OFF)
