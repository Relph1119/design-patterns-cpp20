#pragma once

#include <memory>
#include "HotDrink.h"
#include "HotDrinkFactory.h"

struct HotDrink;

struct CoffeeFactory : HotDrinkFactory {
    [[nodiscard]] unique_ptr<HotDrink> make() const override {
        return make_unique<Coffee>();
    }
};