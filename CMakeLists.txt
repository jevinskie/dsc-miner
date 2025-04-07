cmake_minimum_required(VERSION 3.31)

cmake_policy(SET CMP0181 NEW)

project(dsc-miner C CXX)

add_compile_options(-fsanitize=address -fno-omit-frame-pointer -g -O0)
add_link_options(-fsanitize=address -O0)

add_subdirectory(3rdparty)
add_subdirectory(lib)
add_subdirectory(tools)
