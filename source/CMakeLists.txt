cmake_minimum_required(VERSION 3.10)

project(lizst VERSION 1.1.6)

add_executable(lst main.c)

install(TARGETS lst DESTINATION bin)
