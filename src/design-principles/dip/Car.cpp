//
// Created by HRF on 2023/2/22.
// P20
// 依赖倒置原则：
// 1. 高层模块不应该依赖低层模块，它们都应该依赖抽象接口
// 2. 抽象接口不应该依赖细节，细节应该依赖抽象接口
//

#include <iostream>
#include <string>
#include "di.hpp"
using namespace std;
namespace di = boost::di;

struct Engine {
    float volume = 5;
    int horse_power = 400;

    Engine(float _volume, int _horse_power) : volume{_volume}, horse_power{_horse_power} {}

    friend ostream &operator<<(ostream &os, const Engine &obj) {
        return os
                << "volume: " << obj.volume
                << " horse_power: " << obj.horse_power << endl;
    }

    friend ostream &operator<<(ostream &os, const shared_ptr<Engine> &obj) {
        return os
        << "volume: " << obj->volume
        << " horse_power: " << obj->horse_power << endl;
    }
};

struct ILogger {
    virtual ~ILogger() = default;

    virtual void Log(const string &s) = 0;
};

struct ConsoleLogger : ILogger {
    ConsoleLogger() = default;

    void Log(const string &s) override {
        cout << "LOG: " << s.c_str() << endl;
    }
};

struct Car {
    shared_ptr<Engine> engine;
    shared_ptr<ILogger> logger;

    Car(shared_ptr<Engine> engine, const shared_ptr<ILogger> &logger) : engine{move(engine)}, logger{logger} {
        logger->Log("making a car");
    }

    friend ostream &operator<<(ostream &os, const Car &obj) {
        return os << "car with engine: " << obj.engine << endl;
    }

    friend ostream &operator<<(ostream &os, const shared_ptr<Car>& car) {
        return os << "car with engine: " << car->engine << endl;
    }
};

int main() {
    auto injector = di::make_injector(
            di::bind<ILogger>().to<ConsoleLogger>(),
            di::bind<Engine>().to(make_shared<Engine>(5, 100)));
    auto car = injector.create<shared_ptr<Car>>();
    cout << car << endl;
    return 0;
}
