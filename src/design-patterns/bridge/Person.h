//
// Created by HRF on 2023/3/2.
//

#ifndef DESIGN_PATTERNS_CPP20_PERSON_H
#define DESIGN_PATTERNS_CPP20_PERSON_H

#pragma once

#include <string>

struct Person {
    std::string name;

    class PersonImpl;

    PersonImpl *impl;

    Person();

    ~Person();

    void greet();
};

#endif //DESIGN_PATTERNS_CPP20_PERSON_H
