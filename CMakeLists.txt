cmake_minimum_required(VERSION 3.22)

project(CppEngine
    VERSION 0.0.1
    DESCRIPTION "3D game engine written in C++"
    LANGUAGES CXX
)

set(CMAKE_CXX STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE ENGINE_SRC src/*.cpp)

add_library(cppengine STATIC src/**/*.cpp)
target_include_directories(cppengine PUBLIC include) 