cmake_minimum_required(VERSION 3.20)
project(dictionary C)

set(CMAKE_C_STANDARD 99)

add_executable(dictionary main.c BTree.c BTree.h)
