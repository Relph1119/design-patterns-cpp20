#pragma once

#include "HotDrink.h"

/**
 * 抽象工厂，仅提供接口，不提供具体实现
 */
struct HotDrinkFactory {
    [[nodiscard]] virtual unique_ptr<HotDrink> make() const = 0;
};