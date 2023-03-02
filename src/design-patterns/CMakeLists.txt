# 设计模式
# 第2章 构造器模式
add_executable(html_builder builder/HtmlBuilder.cpp)
add_executable(tag_builder builder/Tag.cpp)
add_executable(person_builder builder/PersonBuilder.cpp)
add_executable(email_builder builder/EmailBuilder.cpp)
add_executable(person_builder_ext builder/PersonBuilderExt.cpp)

# 第3章 工厂方法和抽象工程模式
add_executable(factory_method factory_method/main.cpp
        factory_method/Wall.cpp
        factory_method/Material.cpp
        factory_method/SolidWall.cpp
        factory_method/WallFactory.cpp)
add_executable(abstract_factory abstract_factory/main.cpp)

# 第4章 原型模式
add_executable(contract_copy prototype/ContactCopy.cpp)
add_executable(extended_address prototype/ExtendedAddress.cpp)
add_executable(serialization_address prototype/SerializationAddress.cpp)
add_executable(employee_factory prototype/EmployeeFactory.cpp)

# 第5章 单例模式
add_executable(singleton_database singleton/SingletonDatabase.cpp)
target_link_libraries(singleton_database gtest gtest_main)
add_executable(per_thread_singleton singleton/PerThreadSingleton.cpp)

# 第6章 适配器模式
add_executable(adapter adapter/AdapterGeometry.cpp)

# 第7章 桥接模式
add_executable(pimpl bridge/Person.cpp)
add_executable(raster_renderer_bridge bridge/RasterRenderer.cpp)

