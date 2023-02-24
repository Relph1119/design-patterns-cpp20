//
// Created by HRF on 2023/2/24.
//
#pragma once
#include <ostream>

using namespace std;

class Point2D {
public:
    int x, y;

    Point2D(const int x, const int y): x{x}, y{y} {}

    friend ostream &operator<<(ostream &os, const Point2D &point) {
        os << "(" << point.x << "," << point.y << ")";
        return os;
    }
};