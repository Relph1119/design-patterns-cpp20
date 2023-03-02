//
// Created by HRF on 2023/3/2.
// P109-111
// 装饰器模式：函数装饰器
// 函数装饰器可以封装代码或特定函数，允许组合行为
//

#include <iostream>
#include <functional>
#include <utility>

using namespace std;

struct Logger {
    function<void()> func;
    string name;

    Logger(const function<void()> &func, string name) : func{func}, name{std::move(name)} {}

    void operator()() const {
        cout << "Entering " << name << "\n";
        func();
        cout << "Exiting " << name << "\n";
    }
};

template<typename Func>
struct Logger2 {
    Func func;
    string name;

    Logger2(const Func &func, const string &name) : func{func}, name{name} {}

    void operator()() const {
        cout << "Entering " << name << "\n";
        func();
        cout << "Exiting " << name << "\n";
    }
};

template<typename Func>
auto make_logger2(Func func, const string &name) {
    return Logger2<Func>{func, name};
}



int main() {
    Logger([]() { cout << "Hello\n"; }, "HelloFunction")();

    auto call = make_logger2([]() { cout << "Hello!" << endl; }, "HelloFunction");
    call();
}