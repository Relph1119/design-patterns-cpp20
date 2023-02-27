//
// Created by HRF on 2023/2/27.
// P60
// 原型工厂
//

#include <iostream>
#include <string>
#include <memory>
#include <utility>

using namespace std;

class Address {
public:
    string street, city;
    int suite;

    Address(const string &street, const string &city, const int suite)
            : street{street},
              city{city},
              suite{suite} {
    }

    friend ostream &operator<<(ostream &os, const Address &obj) {
        return os
                << "street: " << obj.street
                << " city: " << obj.city
                << " suite: " << obj.suite;
    }
};

class Contact {
public:
    string name;
    Address *address;

    Contact(string name, Address *address)
            : name{std::move(name)}, address{address} {
    }

    Contact(const Contact &other)
            : name{other.name}, address{new Address{*other.address}} {}

    Contact &operator=(const Contact &other) {
        if (this == &other)
            return *this;
        name = other.name;
        address = other.address;
        return *this;
    }

    ~Contact() {
        delete address;
    }

    friend ostream &operator<<(ostream &os, const Contact &obj) {
        return os
                << "name: " << obj.name
                << " works at " << *obj.address;
    }
};

class EmployeeFactory {
    static Contact main;
    static Contact aux;

    static unique_ptr<Contact> NewEmployee(string name, int suite, Contact &proto) {
        auto result = make_unique<Contact>(proto);
        result->name = std::move(name);
        result->address->suite = suite;
        return result;
    }

public:
    static unique_ptr<Contact> NewMainOfficeEmployee(string name, int suite) {
        return NewEmployee(std::move(name), suite, main);
    }

    static unique_ptr<Contact> NewAuxOfficeEmployee(string name, int suite) {
        return NewEmployee(std::move(name), suite, aux);
    }
};

Contact EmployeeFactory::main{ "", new Address{ "123 East Dr", "London", 0 } };
Contact EmployeeFactory::aux{ "", new Address{ "123B East Dr", "London", 0 } };

int main() {
    auto john = EmployeeFactory::NewAuxOfficeEmployee("John Doe", 123);
    auto jane = EmployeeFactory::NewMainOfficeEmployee("Jane Doe", 125);

    cout << *john << endl;
    cout << *jane << endl;

    return 0;
}
