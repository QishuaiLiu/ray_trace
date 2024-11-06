cmake_minimum_required(VERSION 3.15)

project(parallel_test)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_ONE_WEEK
   color.h
    vec3.h
    main.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_ONE_WEEK})
