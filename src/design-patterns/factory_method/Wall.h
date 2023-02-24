//
// Created by HRF on 2023/2/24.
//
#pragma once

#include "Point2D.hpp"

class Wall {
    Point2D start, end;
    int elevation, height;
protected:
    Wall(Point2D start, Point2D end, int elevation, int height)
            : start{start}, end{end}, elevation{elevation}, height{height} {}

    // but now you need
    friend class WallFactory;
public:
    virtual ~Wall() = default;

    friend ostream &operator<<(ostream &os, const Wall &wall) {
        os << "start: " << wall.start
           << " end: " << wall.end
           << " elevation: " << wall.elevation
           << " height: " << wall.height;
        return os;
    }

    static bool intersects(const Wall &other) {
        return false;
    }
private:
    class BasicWallFactory {
        friend class Wall;
        BasicWallFactory() = default;
    public:
        shared_ptr<Wall> create(const Point2D start, const Point2D end, const int elevation, const int height) {
            Wall *wall = new Wall(start, end, elevation, height);
            return shared_ptr<Wall>(wall);
        }
    };
public:
    static BasicWallFactory factory;
};
