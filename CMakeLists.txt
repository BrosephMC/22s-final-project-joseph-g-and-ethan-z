cmake_minimum_required(VERSION 3.20)
project(22s_final_proj)

set(CMAKE_CXX_STANDARD 14)

add_executable(22s_final_proj main.cpp catch_setup.cpp DSAVLTree.h IndexHandler.cpp IndexHandler.h QueryProcessor.cpp QueryProcessor.h DocumentParser.cpp DocumentParser.h SearchEngine.cpp SearchEngine.h)
