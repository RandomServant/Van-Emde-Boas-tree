cmake_minimum_required(VERSION 3.20)
project(Van_EmdeBoas_tree)

set(CMAKE_CXX_STANDARD 23)

add_executable(Van_EmdeBoas_tree main.cpp "vEB Tree/VanEmdeBoasTree.cpp" "vEB Tree/VanEmdeBoasTree.h" "Testing/Testing.cpp" "Testing/Testing.h" "Testing/TestsGenerator.h" "Testing/TestsGenerator.cpp" "FisherYatesShuffle/FisherYatesShuffle.cpp" "FisherYatesShuffle/FisherYatesShuffle.h")
