cmake_minimum_required(VERSION 3.20)

project(CppEngine LANGUAGES CXX)

add_library(CppEngine)

target_compile_features(CppEngine PUBLIC cxx_std_20)

target_include_directories(CppEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB_RECURSE ENGINE_SOURCES
    CONFIGURE_DEPENDS
    src/CppEngine/*.cpp
)

file(GLOB_RECURSE ENGINE_HEADERS
    CONFIGURE_DEPENDS
    include/CppEngine/*.h
    include/CppEngine/*.hpp
)

target_sources(CppEngine
    PRIVATE 
        ${ENGINE_SOURCES}
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS include
        FILES ${ENGINE_HEADERS}
)