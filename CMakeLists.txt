cmake_minimum_required(VERSION 3.16)

project(22s_final_proj)

set(CMAKE_CXX_STANDARD 14)

link_libraries(stdc++fs)

add_executable(22s_final_proj main.cpp catch_setup.cpp avlTree.h search_engine.cpp search_engine.h test.cpp porter2_stemmer-master/porter2_stemmer.h porter2_stemmer-master/porter2_stemmer.cpp stop.h)
