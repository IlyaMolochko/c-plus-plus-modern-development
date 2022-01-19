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

//class Person {
//public:
//    // Вы можете вставлять сюда различные реализации класса,
//    // чтобы проверить, что ваши тесты пропускают корректный код
//    // и ловят некорректный
//    void ChangeFirstName(int year, const string& first_name) {
//    }
//    void ChangeLastName(int year, const string& last_name) {
//    }
//    string GetFullName(int year) {
//    }
//};

void Tests() {
    Person person;

    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1969, "Sergeeva");
    AssertEqual(person.GetFullName(1964), "Incognito");
    AssertEqual(person.GetFullName(1966), "Polina with unknown last name");
    AssertEqual(person.GetFullName(1970), "Polina Sergeeva");

    person.ChangeFirstName(1967, "Appolinaria");
    AssertEqual(person.GetFullName(1968), "Appolinaria with unknown last name");
    AssertEqual(person.GetFullName(1970), "Appolinaria Sergeeva");

    person.ChangeLastName(1959, "Volkova");
    AssertEqual(person.GetFullName(1964), "Volkova with unknown first name");
    AssertEqual(person.GetFullName(1966), "Polina Volkova");
    AssertEqual(person.GetFullName(1978), "Appolinaria Sergeeva");

    person.ChangeLastName(1971, "Sergeeva-Volkova");
    AssertEqual(person.GetFullName(1978), "Appolinaria Sergeeva-Volkova");

}

int main() {
    TestRunner runner;
    runner.RunTest(Tests, "Tests");
    // добавьте сюда свои тесты
    return 0;
}