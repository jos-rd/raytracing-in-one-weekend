cmake_minimum_required(VERSION 3.5)

project(src LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(HEADERS
    vec3.h
    color.h
    ray.h
    traceable.h
    sphere.h
)

set(SOURCES
    main.cpp
)


add_executable(src main.cpp)
