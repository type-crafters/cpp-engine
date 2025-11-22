cmake_minimum_required(VERSION 3.22)

# Project Name
project(CPPEngine LANGUAGES CXX)

# C++ Version
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
file(GLOB_RECURSE ENGINE_SRC src/*.cpp)

# Create library target
add_library(cppeng STATIC ${ENGINE_SRC})

# Public headers
target_include_directories(cppeng PUBLIC include)
