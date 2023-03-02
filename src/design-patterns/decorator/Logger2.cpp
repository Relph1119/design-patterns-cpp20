//
// Created by HRF on 2023/3/2.
// P109-111
// 装饰器模式：函数装饰器
//

#include <iostream>
#include <functional>
#include <utility>

using namespace std;

double add(double a, double b) {
    cout << a << "+" << b << "=" << (a + b) << endl;
    return a + b;
}

template<typename T>
struct Logger3{};

template<typename R, typename... Args>
struct Logger3<R(Args...)> {
    Logger3(function<R(Args...)> func, string name) : func{std::move(func)}, name{std::move(name)} {};

    R operator() (Args... args) {
        cout << "Entering " << name << endl;
        R result = func(args...);
        cout << "Exiting " << name << "\n";
        return result;
    }

    function<R(Args...)> func;
    string name;
};

template<typename R, typename... Args>
auto make_logger3(R (*func)(Args...), const string & name) {
    return Logger3<R(Args...)>(
            function<R(Args...)>(func), name);
}

int main() {
    auto logged_add = make_logger3(add, "Add");
    auto result = logged_add(2, 3);
    cout << result << endl;
    return 0;
}