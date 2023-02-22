//
// Created by HRF on 2023/2/22.
// 开闭原则：不必返回到已经编写喝测试的代码来修改它
//

#include <iostream>
#include <vector>

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
struct AndSpecification;

template<typename T>
struct Specification {
    virtual bool is_satisfied(T *item) = 0;

    AndSpecification<T> operator&&(Specification &other) {
        return AndSpecification<T>(*this, other);
    }
};

template<typename T>
struct Filter {
    virtual vector<T *> filter(vector<T *> items, Specification<T> &&spec) const = 0;
};

template<typename T>
struct BetterFilter : Filter<T> {
    vector<T *> filter(vector<T *> items, Specification<T> &&spec) const override {
        vector<T *> result;
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
struct AndSpecification : Specification<T> {
    Specification<T> &first;
    Specification<T> &second;

    AndSpecification(Specification<T> &first, Specification<T> &second) : first{first}, second{second} {}

    bool is_satisfied(T *item) override {
        return first.is_satisfied(item) && second.is_satisfied(item);
    }
};

int main() {
    Product apple{"Apple", Color::Green, Size::Small};
    Product tree{"Tree", Color::Green, Size::Large};
    Product house{"House", Color::Blue, Size::Large};

    vector<Product *> all{&apple, &tree, &house};

    BetterFilter<Product> bf;
    SizeSpecification large(Size::Large);
    ColorSpecification green(Color::Green);

    auto green_things = bf.filter(all, forward<Specification<Product>>(green));
    for (auto &x: green_things) {
        cout << x->name << " is green." << endl;
    }

    auto big_green_things = bf.filter(all, green && large);
    for (auto &x: big_green_things) {
        cout << x->name << " is large and green." << endl;
    }
    return 0;
}