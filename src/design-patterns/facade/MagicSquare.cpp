//
// Created by HRF on 2023/3/2.
// P113-116
// 外观模式：幻方生成器
//

#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

struct Generator {
    virtual vector<int> generate(const int count) const {
        vector<int> result(count);
        ::generate(result.begin(), result.end(), [&]() {return 1+ rand()%9; });
        return result;
    }
};

struct Splitter {
    vector<vector<int>> split(vector<vector<int>> array) const {

    }
};

struct Verifier {
    bool verify(vector<vector<int>> array) const {
        if (array.empty())
            return false;
        auto expected = accumulate(array[0].begin(), array[0].end(), 0);
        return all_of(array.begin(), array.end(), [=](auto & inner) {
           return accumulate(inner.begin(), inner.end(), 0) == expected;
        });
    }
};

