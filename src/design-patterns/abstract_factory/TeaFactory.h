#pragma once

#include "HotDrinkFactory.h"

struct TeaFactory : HotDrinkFactory {
    [[nodiscard]] unique_ptr<HotDrink> make() const override {
        return make_unique<Tea>();
    }
};