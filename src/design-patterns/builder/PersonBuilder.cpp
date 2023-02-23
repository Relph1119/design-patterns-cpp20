//
// Created by HRF on 2023/2/23.
// P32
// 组合构造器
//

#include <string>
#include <memory>
#include <iostream>
#include <utility>

using namespace std;

class PersonBuilderBase;
class PersonAddressBuilder;
class PersonJobBuilder;
class PersonBuilder;

class Person {
public:
    Person() = default;

    string street_address;
    string post_code;
    string city;
    string company_name;
    string position;
    long annual_income = 0;

    static unique_ptr<PersonBuilder> create() {
        return make_unique<PersonBuilder>();
    }

    friend ostream &operator<<(ostream &os, const Person &person) {
        os << "A person";
        if (!person.street_address.empty()) {
            os << " lives ";
            os << (!person.street_address.empty() ? "at " + person.street_address :"");
            os << (!person.post_code.empty() ? " with " + person.post_code :"");
            os << (!person.city.empty() ? " in " + person.city :"");
        }

        if (!person.position.empty()) {
            os << " and works ";
            os << (!person.company_name.empty() ? "at " + person.company_name :"");
            os << (!person.position.empty() ? " as a " + person.position :"");
            os << (person.annual_income != 0 ? " earning " + to_string(person.annual_income) :"");
        }

        return os;
    }
};

class PersonBuilderBase {
protected:
    Person &person;;
public:
    operator Person() {
        return move(person);
    }

    [[nodiscard]] PersonAddressBuilder lives() const;

    [[nodiscard]] PersonJobBuilder works() const;

    explicit PersonBuilderBase(Person &person) : person{person} {}
};

class PersonBuilder : public PersonBuilderBase {
    Person p;
public:
    PersonBuilder() : PersonBuilderBase{p} {}
};

class PersonAddressBuilder : public PersonBuilderBase {
    string postcode;
    string city;
    typedef PersonAddressBuilder self;
public:
    explicit PersonAddressBuilder(Person &person) : PersonBuilderBase{person} {}

    self &at(string street_address) {
        person.street_address = std::move(street_address);
        return *this;
    }

    self &with_postcode(string post_code) {
        person.post_code = std::move(post_code);
        return *this;
    }

    self &in(string _city) {
        person.city = std::move(_city);
        return *this;
    }
};

class PersonJobBuilder : public PersonBuilderBase {
    typedef PersonJobBuilder self;
public:
    explicit PersonJobBuilder(Person &person) : PersonBuilderBase{person} {}

    self &at(string position) {
        person.position = std::move(position);
        return *this;
    }

    self &as_a(string company_name) {
        person.company_name = std::move(company_name);
        return *this;
    }

    self &earning(long annual_income) {
        person.annual_income = annual_income;
        return *this;
    }
};

PersonAddressBuilder PersonBuilderBase::lives() const {
    return PersonAddressBuilder(this->person);
}

PersonJobBuilder PersonBuilderBase::works() const {
    return PersonJobBuilder(this->person);
}

int main() {
    Person p = Person::create()
            ->lives().at("123 London Road")
            .with_postcode("SW1 1GB")
            .in("London")
            .works().at("PragmaSoft")
            .as_a("Consultant")
            .earning(10e6);
    cout << p << endl;
    return 0;
}

