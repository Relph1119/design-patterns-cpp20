//
// Created by HRF on 2023/2/27.
// P57~P58
// 虚构造函数
//

#include <string>
#include <iostream>

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

    virtual Address *clone() {
        return new Address{street, city, suite};
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
            : name{name}, address{address} {
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

class ExtendedAddress : public Address {
public:
    string country, postcode;

    ExtendedAddress(const string &street, const string &city,
                    const int suite, const string &country,
                    const string &postcode) : Address(street, city, suite), country{country}, postcode{postcode} {
    }

    ExtendedAddress *clone() override {
        return new ExtendedAddress(*this);
    }
};

int main() {
    ExtendedAddress ea{"123 West Dr", "London", 123, "UK", "SW1010EG"};
    Address &a = ea;
    auto cloned = a.clone();
    cout << *cloned << endl;
}

