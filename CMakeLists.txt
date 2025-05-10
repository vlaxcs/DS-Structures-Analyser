cmake_minimum_required(VERSION 3.30)
project(T2SD)

set(CMAKE_CXX_STANDARD 26)

add_executable(T2SD main.cpp
            src/DataStructure.cpp
            src/SkipList.cpp
            src/SplayTree.cpp
            src/Tester.cpp)

target_include_directories(T2SD PUBLIC include)
