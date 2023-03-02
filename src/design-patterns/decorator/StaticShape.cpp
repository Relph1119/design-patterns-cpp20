//
// Created by HRF on 2023/3/2.
// P107-P108
// 装饰器模式：静态装饰器
//

#include <string>
#include <sstream>
#include <iostream>
#include <utility>

using namespace std;

struct Shape {
    [[nodiscard]] virtual string str() const = 0;
};

struct Circle : Shape {
    float radius;

    Circle(const float radius) : radius{radius} {}

    void resize(float factor) { radius *= factor; }

    string str() const override {
        ostringstream oss;
        oss << "A circle of radius " << radius;
        return oss.str();
    }
};

struct Square : Shape {
    float size;

    Square(const float size) : size{size} {}

    string str() const override {
        ostringstream oss;
        oss << "A square with side " << size;
        return oss.str();
    }
};

template<typename T>
struct ColoredShape : T {
    static_assert(is_base_of_v<Shape, T>, "Template argument must be a Shape");

    string color;

    template<typename... Args>
    explicit ColoredShape(string color, Args... args) : T(forward<Args>(args)...), color{std::move(color)} {}

    string str() const override {
        ostringstream oss;
        oss << T::str() << " has the color " << color;
        return oss.str();
    }

    void make_dark() {
        if (constexpr auto dark = "dark "; !color.starts_with(dark)) {
            color.insert(0, dark);
        }
    }
};

template<typename T>
struct TransparentShape: T {
    uint8_t transparency;

    template<typename... Args>
    explicit TransparentShape(const uint8_t transparency, Args... args): T(forward<Args>(args)...), transparency{transparency} {}

    string str() const override {
        ostringstream oss;
        oss << T::str() << " has "
        << static_cast<float>(transparency) / 255.f * 100.f
        << "% transparency";
        return oss.str();
    }
};

int main() {
    ColoredShape<TransparentShape<Square>> square{"red", 51, 5};
    cout << square.str() << endl;
    return 0;
}