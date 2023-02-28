# 《C++20设计模式》读书笔记

书籍原版代码：https://github.com/Apress/design-patterns-modern-cpp20

## 运行环境

- C++20版本：gcc 12.2.0
- Boost版本：1.81.0

1. 编译Boost
需要提前安装VS2019以上版本，打开`Developer Command Prompt for VS 2019`
参考：https://blog.csdn.net/qq_36163982/article/details/122438593
```shell
cd D:\CppLibs\boost_1_81_0
bootstrap msvc
b2 install threading=multi link=static toolset=msvc-14.2 --prefix="..\Boost" debug release
```

## 学习总结
