//
// Created by HRF on 2023/3/2.
// P85~86
// Pimpl模型
//

#include "Person.h"

struct Person::PersonImpl {
    void greet(Person *p);
};

void Person::PersonImpl::greet(Person *p) {
    printf("hello %s", p->name.c_str());
}

Person::Person()
        : impl(new PersonImpl) {
}

Person::~Person() {
    delete impl;
}

void Person::greet() {
    impl->greet(this);
}

int main() {
    Person p{};
    p.name = "John";
    p.greet();
    return 0;
}