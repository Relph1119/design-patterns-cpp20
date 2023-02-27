cmake_minimum_required(VERSION 3.20)
project(design-patterns-cpp20)

set(CMAKE_CXX_STANDARD 20)

include_directories(libs/boost/)
include_directories(D:\\CppLibs\\Boost\\include\\boost-1_81)
link_directories(D:\\CppLibs\\Boost\\lib)

# 设计原则
add_executable(srp src/design-principles/srp/Journal.cpp)
add_executable(ocp1 src/design-principles/ocp/Product1.cpp)
add_executable(ocp2 src/design-principles/ocp/Product2.cpp)
add_executable(lsp src/design-principles/lsp/Rectangle.cpp)
add_executable(isp src/design-principles/isp/Print.cpp)
add_executable(dip src/design-principles/dip/Car.cpp)

# 设计模式
# 第2章 构造器模式
add_executable(html_builder src/design-patterns/builder/HtmlBuilder.cpp)
add_executable(tag_builder src/design-patterns/builder/Tag.cpp)
add_executable(person_builder src/design-patterns/builder/PersonBuilder.cpp)
add_executable(email_builder src/design-patterns/builder/EmailBuilder.cpp)
add_executable(person_builder_ext src/design-patterns/builder/PersonBuilderExt.cpp)

# 第3章 工厂方法和抽象工程模式
add_executable(factory_method src/design-patterns/factory_method/main.cpp
        src/design-patterns/factory_method/Wall.cpp
        src/design-patterns/factory_method/Material.cpp
        src/design-patterns/factory_method/SolidWall.cpp
        src/design-patterns/factory_method/WallFactory.cpp)
add_executable(abstract_factory src/design-patterns/abstract_factory/main.cpp)

# 第4章 原型模式
add_executable(contract_copy src/design-patterns/prototype/ContactCopy.cpp)
add_executable(extended_address src/design-patterns/prototype/ExtendedAddress.cpp)
add_executable(serialization_address src/design-patterns/prototype/SerializationAddress.cpp)
add_executable(employee_factory src/design-patterns/prototype/EmployeeFactory.cpp)