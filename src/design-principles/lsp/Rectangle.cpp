//
// Created by HRF on 2023/2/22.
// P15 里氏替换原则
//

#include <iostream>

using namespace std;

class Rectangle {
protected:
    int width, height;
public:
    Rectangle(const int width, const int height) : width{width}, height{height} {}

    int get_width() const { return width; }

    virtual void set_width(const int width) { this->width = width; }

    int get_height() const { return height; }

    virtual void set_height(const int height) { this->height = height; }

    int area() const { return width * height; }
};

class Square : public Rectangle {
public:
    explicit Square(int size) : Rectangle(size, size) {}

    void set_width(const int width) override { this->width = height = width; }

    void set_height(const int height) override { this->height = width = height; }
};

void process(Rectangle& r) {
    int w = r.get_width();
    r.set_height(10);
    cout << "expected area = " << (w * 10) << ", got " << r.area() << endl;
}

int main() {
    Rectangle r{10, 5};
    process(r);

    Square s{5};
    process(s);

    return 0;
}