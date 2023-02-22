//
// Created by HRF on 2023/2/22.
// 单一职责原则：每个类只有一个职责。
//

#include <string>
#include <utility>
#include <vector>
#include <fstream>

using namespace std;

struct Journal {
    string title;
    vector<string> entries;

    explicit Journal(string title) : title{std::move(title)} {}
    void add(const string & entry);
};

void Journal::add(const string & entry) {
    static int count = 1;
    entries.push_back(to_string((count++)) + ": " + entry);
}

struct PersistenceManager {
    static void save(const Journal& j, const string &filename) {
        ofstream ofs(filename);
        for(auto &s : j.entries) {
            ofs << s << endl;
        }
    }
};

int main() {
    Journal j{"Dear Diary"};
    j.add("I cried today");
    j.add("I ate a bug");
    PersistenceManager::save(j, "journal.txt");
    return 0;
}
