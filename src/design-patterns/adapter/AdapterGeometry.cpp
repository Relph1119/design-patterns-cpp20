//
// Created by HRF on 2023/2/28.
// P79~P80
// 适配器
//

#include <vector>
#include <memory>
#include <map>
#include <iostream>
#include "BasicGeometry.h"

using namespace std;

struct LineToPointAdapter {
    typedef vector<Point> Points;

    explicit LineToPointAdapter(Line &line) {
        int left = min(line.start.x, line.end.x);
        int right = max(line.start.x, line.end.x);
        int top = min(line.start.y, line.end.y);
        int bottom = max(line.start.y, line.end.y);
        int dx = right - left;
        int dy = line.end.y - line.start.y;

        // 仅处理水平或垂直的线段
        if (dx == 0) {
            // 垂直线段
            for (int y = top; y <= bottom; ++y) {
                points.emplace_back(Point{left, y});
            }
        } else if (dy == 0) {
            for (int x = left; x <= right; ++x) {
                points.emplace_back(Point{x, top});
            }
        }
    }

    virtual Points::iterator begin() { return points.begin(); }

    virtual Points::iterator end() { return points.end(); }

    friend ostream &operator<<(ostream &os, const LineToPointAdapter &adapter) {
        for (const auto &point : adapter.points) {
            os << point;
        }
        return os;
    }

private:
    Points points;
};

struct LineToPointCachingAdapter {
    typedef vector<Point> Points;

    explicit LineToPointCachingAdapter(Line &line) {
        boost::hash<Line> hash;
        line_hash = hash(line);
        if (cache.find(line_hash) != cache.end())
            return; // we already have it

        Points points;

        int left = min(line.start.x, line.end.x);
        int right = max(line.start.x, line.end.x);
        int top = min(line.start.y, line.end.y);
        int bottom = max(line.start.y, line.end.y);
        int dx = right - left;
        int dy = line.end.y - line.start.y;

        // only vertical or horizontal lines
        if (dx == 0) {
            // vertical
            for (int y = top; y <= bottom; ++y) {
                points.emplace_back(Point{left, y});
            }
        } else if (dy == 0) {
            for (int x = left; x <= right; ++x) {
                points.emplace_back(Point{x, top});
            }
        }

        cache[line_hash] = points;
    }

    virtual Points::iterator begin() { return cache[line_hash].begin(); }

    virtual Points::iterator end() { return cache[line_hash].end(); }

private:
    size_t line_hash;
    static map<size_t, Points> cache;
};

int main() {
    vector<shared_ptr<VectorObject>> vectorObjects{
        make_shared<VectorRectangle>(10, 10, 100, 100),
        make_shared<VectorRectangle>(30, 30, 60, 60)
    };

    for (const auto & obj : vectorObjects) {
        for (auto line : *obj) {
            LineToPointAdapter lpo{line};
            cout << lpo << endl;
        }
    }
    return 0;
}
