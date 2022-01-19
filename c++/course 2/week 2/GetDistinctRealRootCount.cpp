#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template<class T>
ostream &operator<<(ostream &os, const vector<T> &s) {
    os << "{";
    bool first = true;
    for (const auto &x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template<class T>
ostream &operator<<(ostream &os, const set<T> &s) {
    os << "{";
    bool first = true;
    for (const auto &x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template<class K, class V>
ostream &operator<<(ostream &os, const map<K, V> &m) {
    os << "{";
    bool first = true;
    for (const auto &kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template<class T, class U>
void AssertEqual(const T &t, const U &u, const string &hint = {}) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string &hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    template<class TestFunc>
    void RunTest(TestFunc func, const string &test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        } catch (exception &e) {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        } catch (...) {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};

//int GetDistinctRealRootCount(double a, double b, double c) {
//    // Вы можете вставлять сюда различные реализации функции,
//    // чтобы проверить, что ваши тесты пропускают корректный код
//    // и ловят некорректный
//    double d = b * b - 4 * a * c;
//    if (d == 0 and a != 0){
//        return 1;
//    } else if (a == 0 and d > 0 and b != 0){
//        return 1;
//    } else if (d > 0 and a != 0){
//        return 2;
//    }
//    return 0;
//}

void TestTwoRoots(){
    AssertEqual(GetDistinctRealRootCount(1, 4, 1), 2,
                "x^2 + 4x + 1 = 0 has 2 real roots");
    AssertEqual(GetDistinctRealRootCount(2, 4, 1), 2,
                "2x^2 + 4x + 1 = 0 has 2 real roots");
    AssertEqual(GetDistinctRealRootCount(3, 4, 1), 2,
                "3x^2 + 4x + 1 = 0 has 2 real roots");
    AssertEqual(GetDistinctRealRootCount(1, 4, 3), 2,
                "x^2 + 4x + 3 = 0 has 2 real roots");
    AssertEqual(GetDistinctRealRootCount(1, 4, 2), 2,
                "x^2 + 4x + 2 = 0 has 2 real roots");
    AssertEqual(GetDistinctRealRootCount(-1, 4, -1), 2,
                "-x^2 + 4x - 1 = 0 has 2 real roots");
    AssertEqual(GetDistinctRealRootCount(-10, 4, 10), 2,
                "-10x^2 + 4x + 10 = 0 has 2 real roots");
    AssertEqual(GetDistinctRealRootCount(1000, 4, -1000), 2,
                "1000x^2 + 4x - 1000000 = 0 has 2 real roots");
    AssertEqual(GetDistinctRealRootCount(1, 0, -1), 2,
                "x^2 - 1 = 0 has 2 real roots");
    AssertEqual(GetDistinctRealRootCount(-1, 0, 1), 2,
                "-x^2 + 1 = 0 has 2 real roots");
    AssertEqual(GetDistinctRealRootCount(1, 0, -100), 2,
                "x^2 - 100 = 0 has 2 real roots");
    AssertEqual(GetDistinctRealRootCount(100, 0, -1), 2,
                "100x^2 - 1 = 0 has 2 real roots");
    AssertEqual(GetDistinctRealRootCount(1, 1, 0), 2,
                "x^2 + x = 0 has 2 real roots");
    AssertEqual(GetDistinctRealRootCount(20, -100, 0), 2,
                "20x^2 - 100x = 0 has 2 real roots");
    AssertEqual(GetDistinctRealRootCount(20, 100, 0), 2,
                "20x^2 + 100x = 0 has 2 real roots");
}

void TestOneRoot(){
    AssertEqual(GetDistinctRealRootCount(2, 4, 2), 1,
                "2x^2 + 4x + 2 = 0 has 1 real roots");
    AssertEqual(GetDistinctRealRootCount(-2, 4, -2), 1,
                "-2x^2 + 4x - 2 = 0 has 1 real roots");
    AssertEqual(GetDistinctRealRootCount(4, 4, 1), 1,
                "4x^2 + 4x + 1 = 0 has 1 real roots");
    AssertEqual(GetDistinctRealRootCount(1, 4, 4), 1,
                "x^2 + 4x + 4 = 0 has 1 real roots");
    AssertEqual(GetDistinctRealRootCount(-4, 4, -1), 1,
                "-4x^2 + 4x - 1 = 0 has 1 real roots");
    AssertEqual(GetDistinctRealRootCount(-1, 4, -4), 1,
                "-x^2 + 4x -4 = 0 has 1 real roots");
    AssertEqual(GetDistinctRealRootCount(1, -20, 100), 1,
                "x^2 - 20x + 100 = 0 has 1 real roots");
    AssertEqual(GetDistinctRealRootCount(1, 20, 100), 1,
                "x^2 + 20x + 100 = 0 has 1 real roots");
    AssertEqual(GetDistinctRealRootCount(1, -6, 9), 1,
                "x^2 - 6x + 9 = 0 has 1 real roots");
    AssertEqual(GetDistinctRealRootCount(1, 6, 9), 1,
                "x^2 + 6x + 9 = 0 has 1 real roots");
    AssertEqual(GetDistinctRealRootCount(1, 6, 9), 1,
                "x^2 + 6x + 9 = 0 has 1 real roots");
    AssertEqual(GetDistinctRealRootCount(0, 2, 9), 1,
                "2x + 9 = 0 has 1 real roots");
    AssertEqual(GetDistinctRealRootCount(0, 1, 10), 1,
                "x + 10 = 0 has 1 real roots");
    AssertEqual(GetDistinctRealRootCount(0, 2, -9), 1,
                "2x - 9 = 0 has 1 real roots");
    AssertEqual(GetDistinctRealRootCount(0, 1, -10), 1,
                "x - 10 = 0 has 1 real roots");
    AssertEqual(GetDistinctRealRootCount(0, -2, -9), 1,
                "-2x - 9 = 0 has 1 real roots");
    AssertEqual(GetDistinctRealRootCount(0, -1, -10), 1,
                "-x - 10 = 0 has 1 real roots");
}

void TestNoRoots(){
    AssertEqual(GetDistinctRealRootCount(3, 4, 2), 0,
                "3x^2 + 4x + 2 = 0 has 0 real roots");
    AssertEqual(GetDistinctRealRootCount(8, 4, 1), 0,
                "8x^2 + 4x + 1 = 0 has 0 real roots");
    AssertEqual(GetDistinctRealRootCount(-3, 4, -2), 0,
                "-3x^2 + 4x - 2 = 0 has 0 real roots");
    AssertEqual(GetDistinctRealRootCount(-8, 4, -1), 0,
                "-8x^2 + 4x - 1 = 0 has 0 real roots");
    AssertEqual(GetDistinctRealRootCount(3, 0, 2), 0,
                "3x^2 + 2 = 0 has 0 real roots");
    AssertEqual(GetDistinctRealRootCount(8, 0, 1), 0,
                "8x^2 + 1 = 0 has 0 real roots");
    AssertEqual(GetDistinctRealRootCount(-3, 0, -2), 0,
                "-3x^2 - 2 = 0 has 0 real roots");
    AssertEqual(GetDistinctRealRootCount(-8, 0, -1), 0,
                "-8x^2 - 1 = 0 has 0 real roots");
    AssertEqual(GetDistinctRealRootCount(0, 0, 2), 0,
                "2 = 0 has 0 real roots");
    AssertEqual(GetDistinctRealRootCount(0, 0, 1), 0,
                "1 = 0 has 0 real roots");
    AssertEqual(GetDistinctRealRootCount(0, 0, -2), 0,
                "- 2 = 0 has 0 real roots");
    AssertEqual(GetDistinctRealRootCount(0, 0, -1), 0,
                "- 1 = 0 has 0 real roots");
}

int main() {
    TestRunner runner;
    // добавьте сюда свои тесты
    runner.RunTest(TestTwoRoots, "TestTwoRoots");
    runner.RunTest(TestOneRoot, "TestOneRoot");
    runner.RunTest(TestNoRoots, "TestNoRoots");
    return 0;
}