cmake_minimum_required(VERSION 4.2)
project(xfc CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(external)
add_subdirectory(shared)
add_subdirectory(projects)
