cmake_minimum_required(VERSION 3.20)
project(design-patterns-cpp20)

set(CMAKE_CXX_STANDARD 20)

include_directories(libs/boost/)
include_directories(D:\\CppLibs\\Boost\\include\\boost-1_77)
link_directories(D:\\CppLibs\\Boost\\lib)
include_directories(libs/googletest-1.13.0/googletest/include libs/googletest-1.13.0/googletest)
include_directories(libs/googletest-1.13.0/googlemock/include libs/googletest-1.13.0/googlemock)

add_subdirectory(libs/googletest-1.13.0)
add_subdirectory(src/design-principles)
add_subdirectory(src/design-patterns)