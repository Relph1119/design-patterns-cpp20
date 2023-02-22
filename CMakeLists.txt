cmake_minimum_required(VERSION 3.20)
project(design-patterns-cpp20)

set(CMAKE_CXX_STANDARD 14)

include_directories(libs/boost/)

# 设计原则
add_executable(srp src/design-principles/srp/Journal.cpp)
add_executable(ocp1 src/design-principles/ocp/Product1.cpp)
add_executable(ocp2 src/design-principles/ocp/Product2.cpp)
add_executable(lsp src/design-principles/lsp/Rectangle.cpp)
add_executable(isp src/design-principles/isp/Print.cpp)
add_executable(dip src/design-principles/dip/Car.cpp)