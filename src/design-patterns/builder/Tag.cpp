//
// Created by HRF on 2023/2/23.
// P30
// 对象构建
//

#include <string>
#include <utility>
#include <vector>
#include <iostream>

using namespace std;

struct Tag {
    string name;
    string text;
    vector<Tag> children;
    vector<pair<string, string>> attributes;

    friend ostream &operator<<(ostream &os, const Tag &tag) {
        os << "<" + tag.name;
        for (const auto &attr : tag.attributes){
            os << " " << attr.first << "=\"" << attr.second + "\"";
        }
        os << ">";
        for(auto &c: tag.children) {
            os << "<" + c.name;
            for (const auto &attr : c.attributes){
                os << " " << attr.first << "=\"" << attr.second + "\"";
            }
            os << "/>";
        }
        os << "<" + tag.name + "/>";
        return os;
    }

protected:
    Tag(string name, string text) : name{std::move(name)}, text{std::move(text)} {}

    Tag(string name, const vector<Tag> &children) : name{std::move(name)}, children{children} {}
};

struct P : Tag {
    explicit P(const string &text) : Tag{"p", text} {}

    P(initializer_list<Tag> children) : Tag("p", children) {}
};

struct IMG : Tag {
    explicit IMG(const string &url) : Tag{"img", ""} {
        attributes.emplace_back(pair{"src", url});
    }
};

int main() {
    auto p = P{
            IMG{"http://pokemon.com/pikachu.png"}
    };

    cout << p << endl;
    return 0;
}