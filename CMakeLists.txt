cmake_minimum_required(VERSION 3.10)

project(lizst VERSION 1.1.8)

add_executable(lst src/main.c)

install(TARGETS lst DESTINATION bin)
