//
// Created by HRF on 2023/2/27.
// P58~60
// 序列化
//

#include <string>
#include <iostream>
#include <sstream>
#include <boost/serialization/serialization.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

using namespace std;

class Address {
public:
    string street;
    string city;
    int suite{};
private:
    friend class boost::serialization::access;

    template<class Ar>
    void serialize(Ar &ar, const unsigned int version) {
        ar & street;
        ar & city;
        ar & suite;
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
    Address *address = nullptr;

    ~Contact() {
        delete address;
    }

    friend ostream &operator<<(ostream &os, const Contact &obj) {
        return os
                << "name: " << obj.name
                << " works at " << *obj.address;
    }

private:
    friend class boost::serialization::access;

    template<class Ar>
    void serialize(Ar &ar, const unsigned int version) {
        ar & name;
        ar & address;
    }
};

template<typename T>
T clone(T obj) {
    ostringstream oss;
    boost::archive::text_oarchive oa(oss);
    oa << obj;
    string s = oss.str();

    istringstream iss(oss.str());
    boost::archive::text_iarchive ia(iss);
    T result;
    ia >> result;

    return result;
}

int main() {
//    Contact john{"John Doe", new Address{"123 East Dr", "London"}};
//
//    Contact jane = clone(john);
//    jane.name = "Jane";
//    cout << jane << endl;
    return 0;
}