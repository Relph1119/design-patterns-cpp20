//
// Created by HRF on 2023/2/28.
// P66~68
// 单例模式
//

#include <fstream>
#include <string>
#include <iostream>
#include <map>
#include <boost/lexical_cast.hpp>
#include <gtest/gtest.h>

using namespace std;

class Database {
public:
    virtual int get_population(const std::string &name) = 0;
};

class SingletonDatabase : public Database {
    SingletonDatabase() {
        std::cout << "Initializing database" << std::endl;

        std::ifstream ifs("data/capitals.txt", ios_base::in);
        std::string s, s2;
        if (ifs.is_open()) {
            while (getline(ifs, s)) {
                getline(ifs, s2);
                int pop = boost::lexical_cast<int>(s2);
                capitals[s] = pop;
            }
        } else {
            cout << "file isn't exist!" << endl;
        }
    }

    std::map<std::string, int> capitals;

public:
    SingletonDatabase(SingletonDatabase const &) = delete;

    void operator=(SingletonDatabase const &) = delete;

    static SingletonDatabase &get() {
        static SingletonDatabase db;
        return db;
    }

    int get_population(const std::string &name) override {
        return capitals[name];
    }
};

struct SingletonRecordFinder {
    int total_population(const std::vector<std::string> &names) {
        int result = 0;
        for (auto &name : names)
            result += SingletonDatabase::get().get_population(name);
        return result;
    }
};

class DummyDatabase : public Database {
    std::map<std::string, int> capitals;
public:
    DummyDatabase() {
        capitals["alpha"] = 1;
        capitals["beta"] = 2;
        capitals["gamma"] = 3;
    }

    int get_population(const std::string &name) override {
        return capitals[name];
    }
};

struct ConfigurableRecordFinder {
    explicit ConfigurableRecordFinder(Database &db)
            : db{db} {
    }

    int total_population(std::vector<std::string> names) const {
        int result = 0;
        for (auto &name : names)
            result += db.get_population(name);
        return result;
    }

    Database &db;
};

TEST(RecordFinderTests, SingletonTotalPopulationTest) {
    SingletonRecordFinder rf;
    std::vector<std::string> names{"Seoul", "Mexico City"};
    int tp = rf.total_population(names);
    EXPECT_EQ(17500000 + 17400000, tp);
}

TEST(RecordFinderTests, DependantTotalPopulationTest) {
    DummyDatabase db{};
    ConfigurableRecordFinder rf{db};
    EXPECT_EQ(4, rf.total_population(
            std::vector<std::string>{"alpha", "gamma"}));
}