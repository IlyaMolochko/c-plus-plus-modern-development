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

//bool IsPalindrom(const string &str) {
//    // Вы можете вставлять сюда различные реализации функции,
//    // чтобы проверить, что ваши тесты пропускают корректный код
//    // и ловят некорректный
//}

void Tests(){
    AssertEqual(IsPalindrom(""), true, "Empty string");
    AssertEqual(IsPalindrom("a"), true, "One char a");
    AssertEqual(IsPalindrom("b"), true, "One char b");
    AssertEqual(IsPalindrom("aa"), true, "Two chars aa");
    AssertEqual(IsPalindrom("aca"), true, "aca");
    AssertEqual(IsPalindrom("acA"), false, "acA");
    AssertEqual(IsPalindrom("Aca"), false, "acA");
    AssertEqual(IsPalindrom("aaaaaaaaaaaaaa"), true, "aaaaaaaaaaaaaa");
    AssertEqual(IsPalindrom("aaaaaaaaaaaaaaa"), true, "aaaaaaaaaaaaaaa");
    AssertEqual(IsPalindrom("acabaca"), true, "acabaca");
    AssertEqual(IsPalindrom("acabbaca"), true, "acabbaca");
    AssertEqual(IsPalindrom("acabacaa"), false, "acabacaa");
    AssertEqual(IsPalindrom("acabac"), false, "acabac");
    AssertEqual(IsPalindrom("a ca b ac a"), true, "a ca b ac a");
    AssertEqual(IsPalindrom(" ba ca b ac ab "), true, " ba ca b ac ab ");
    AssertEqual(IsPalindrom("a ca b  c a"), false, "a ca b  c a");
    AssertEqual(IsPalindrom("a c  b  c a"), true, "a c  b  c a");
    AssertEqual(IsPalindrom("a ca b"), false, "a ca b");
    AssertEqual(IsPalindrom("a ca"), false, "a ca");
    AssertEqual(IsPalindrom("acabAca"), false, "acabAca");
    AssertEqual(IsPalindrom("acAbbaca"), false, "acAbbaca");
    AssertEqual(IsPalindrom("acAbAca"), true, "acAbAca");
    AssertEqual(IsPalindrom("AcabbacA"), true, "AcabbacA");
    AssertEqual(IsPalindrom("aaaaaaaaaaaaaA"), false, "aaaaaaaaaaaaaA");
    AssertEqual(IsPalindrom("AaaaaaaaaaaaaA"), true, "AaaaaaaaaaaaaA");
}

int main() {
    TestRunner runner;
    runner.RunTest(Tests, "Tests");
    // добавьте сюда свои тесты
    return 0;
}