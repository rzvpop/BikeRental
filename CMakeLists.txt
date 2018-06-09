cmake_minimum_required(VERSION 3.10)
project(BikeRental)

set(CMAKE_CXX_STANDARD 14)

add_executable(BikeRental main.cpp set.cpp set.hpp tests.cpp tests.hpp rental.cpp rental.hpp)