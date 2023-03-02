//
// Created by HRF on 2023/3/2.
// P104-P106
// 装饰器模式：动态装饰器
// 动态装饰器可以存储对被装饰对象的引用，并提供动态可组合性，但代价是无法访问底层对象自己的成员。
//

#include <string>
#include <sstream>
#include <iostream>

using namespace std;

struct Shape {
    virtual string str() const = 0;
};

struct Circle : Shape {
    float radius;

    explicit Circle(const float radius) : radius{radius} {}

    void resize(float factor) { radius *= factor; }

    string str() const override {
        ostringstream oss;
        oss << "A circle of radius " << radius;
        return oss.str();
    }
};

struct Square : Shape {
    float length;

    explicit Square(const float length) : length{length} {}

    string str() const override {
        ostringstream oss;
        oss << "A square with side " << length;
        return oss.str();
    }
};

struct ColoredShape : Shape {
    Shape &shape;
    string color;

    ColoredShape(Shape &shape, const string &color) : shape{shape}, color{color} {}

    string str() const override {
        ostringstream oss;
        oss << shape.str() << " has the color " << color;
        return oss.str();
    }

    void make_dark();
};

void ColoredShape::make_dark() {
    if (constexpr auto dark = "dark "; !color.starts_with(dark)) {
        color.insert(0, dark);
    }
}

struct TransparentShape: Shape {
    Shape & shape;
    uint8_t transparency;

    TransparentShape(Shape & shape, const uint8_t transparency) : shape{shape}, transparency{transparency} {}
    string str() const override {
        ostringstream oss;
        oss << shape.str() << " has "
            << static_cast<float>(transparency) / 255.f * 100.f
            << "% transparency";
        return oss.str();
    }
};

int main() {
    Circle circle{0.5f};
    ColoredShape redCircle{circle, "red"};
    cout << redCircle.str() << endl;

    redCircle.make_dark();
    cout << redCircle.str() << endl;

    Square square{3};
    TransparentShape demiSquare{square, 85};
    cout << demiSquare.str() << endl;

    Circle c{23};
    ColoredShape cs{c, "green"};
    TransparentShape myCircle{cs, 64};
    cout << myCircle.str() << endl;

    return 0;
}