//
// Created by HRF on 2023/2/23.
// P43
// 工厂方法
//

#include <iostream>

#include "WallFactory.h"

using namespace std;

int main() {
    const auto main_wall = SolidWall::create_main({0, 0}, {0, 3000}, 2700, 3000);
    cout << main_wall << "\n";

    const auto partition = WallFactory::create_partition({2000, 0}, {2000, 4000}, 0, 2700);
    cout << *partition << "\n";

    const auto also_partition =
            WallFactory::create_wall(WallType::partition, {0, 0}, {5000, 0}, 0, 4200);
    if (also_partition)
        cout << *dynamic_pointer_cast<SolidWall>(also_partition) << "\n";

    auto basic = Wall::factory.create({0, 0}, {5000, 0}, 0, 3000);
    cout << *basic << "\n";
    return 0;
}

