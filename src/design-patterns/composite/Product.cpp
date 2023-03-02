//
// Created by HRF on 2023/3/2.
// P100-P101
// 组合模式的规范
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

enum class Color {
    Red, Green, Blue
};
enum class Size {
    Small, Medium, Large
};

struct Product {
    string name;
    Color color;
    Size size;
};

template<typename T>
struct Specification {
    virtual bool is_satisfied(T *item) = 0;
};

template<typename T>
struct Filter {
    virtual vector<T *> filter(vector<T *> items, Specification<T> &spec) const = 0;
};

struct BetterFilter : Filter<Product> {
    vector<Product *> filter(vector<Product *> items, Specification<Product> &spec) const override {
        vector<Product *> result;
        for (auto &p : items) {
            if (spec.is_satisfied(p)) {
                result.push_back(p);
            }
        }
        return result;
    }
};

struct ColorSpecification : Specification<Product> {
    Color color;

    explicit ColorSpecification(const Color color) : color{color} {}

    bool is_satisfied(Product *item) override {
        return item->color == color;
    }
};

struct SizeSpecification : Specification<Product> {
    Size size;

    explicit SizeSpecification(const Size size) : size{size} {}

    bool is_satisfied(Product *item) override {
        return item->size == size;
    }
};

template<typename T>
struct CompositeSpecification : Specification<T> {
protected:
    vector<unique_ptr<Specification<T>>> specs;

    template<typename ... Specs>
    CompositeSpecification(Specs... specs) {
        this->specs.reserve(sizeof...(Specs));
        (this->specs.push_back(make_unique<Specs>(move(specs))), ...);
    }
};

template<typename T>
struct AndSpecification : CompositeSpecification<T> {

    template<typename... Specs>
    AndSpecification(Specs... specs) : CompositeSpecification<T>{specs...} {}

    bool is_satisfied(T *item) override {
        return all_of(this->specs.begin(), this->specs.end(), [=](const auto &s) { return s->is_satisfied(item); });
    }
};

int main() {
    Product apple{"Apple", Color::Green, Size::Small};
    Product tree{"Tree", Color::Green, Size::Large};
    Product house{"House", Color::Blue, Size::Large};

    vector<Product *> all{&apple, &tree, &house};

    BetterFilter bf;
    SizeSpecification large(Size::Large);
    ColorSpecification green(Color::Green);
    AndSpecification<Product> green_and_large{large, green};

    auto green_things = bf.filter(all, green);
    for (auto &x: green_things) {
        cout << x->name << " is green." << endl;
    }

    auto big_green_things = bf.filter(all, green_and_large);
    for (auto &x: big_green_things) {
        cout << x->name << " is large and green." << endl;
    }
    return 0;
}