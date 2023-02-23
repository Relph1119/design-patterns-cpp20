//
// Created by HRF on 2023/2/23.
// P27
// 构造器模式：主要关注复杂对象的创建过程
//

#include <string>
#include <iostream>
#include <utility>
#include <vector>
#include <memory>

using namespace std;

struct HtmlBuilder;

struct HtmlElement {
    string name;
    string text;
    vector<HtmlElement> elements;
    const size_t indent_size = 2;

    static unique_ptr<HtmlBuilder> build(const string &root_name) {
        return make_unique<HtmlBuilder>(root_name);
    }

    string str() const {
        string s;
        s += "<" + name + ">\n";
        for (const auto &item : elements) {
            s += "<" + item.name + ">" + item.text + "</" + item.name + ">\n";
        }
        s += "</" + name +">";
        return s;
    }

    HtmlElement() = default;
    HtmlElement(string name, string text) : name{std::move(name)}, text{std::move(text)} {}
};

struct HtmlBuilder {
    explicit operator HtmlElement() const { return root; }
    HtmlElement root;
    explicit HtmlBuilder(string root_name) {root.name = std::move(root_name); }
    HtmlBuilder add_child(const string& child_name, const string& child_text) {
        root.elements.emplace_back(child_name, child_text);
        return *this;
    }

    string str() const { return root.str(); }
};

int main() {
    auto builder = HtmlElement::build("ul")->add_child("li", "hello").add_child("li", "world");
    cout << builder.str() << endl;
    return 0;
}