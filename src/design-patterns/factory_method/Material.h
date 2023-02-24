//
// Created by HRF on 2023/2/24.
//
#pragma once

enum class Material {
    brick,
    aerated_concrete,
    drywall
};

std::ostream &operator<<(std::ostream &os, Material material);