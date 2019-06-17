cmake_minimum_required(VERSION 3.14)
project(calc VERSION 0.1.0 LANGUAGES C CXX)

add_subdirectory(src)
add_subdirectory(test)

enable_testing()
add_test(NAME calc COMMAND calc-test)
