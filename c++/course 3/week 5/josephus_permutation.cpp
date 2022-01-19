#include "test_runner.h"
#include "profile.h"

#include <cstdint>
#include <iterator>
#include <list>
#include <numeric>
#include <vector>

using namespace std;

template<typename RandomIt>
void MakeJosephusPermutation(RandomIt first, RandomIt last, uint32_t step_size) {
    list<typename RandomIt::value_type> pool;
    move(first, last, back_inserter(pool));
    auto it = pool.begin();
    while (!pool.empty()) {
        *(first++) = move(*it);
        if (pool.size() == 1) {
            break;
        }
        it = pool.erase(it);
        for (uint32_t i = 0; i < step_size - 1; ++i){
            it = (it == pool.end() ? pool.begin() : it);
            it = next(it);
        }
        it = (it == pool.end() ? pool.begin() : it);
    }
}

vector<int> MakeTestVector() {
    vector<int> numbers(100000);
    iota(begin(numbers), end(numbers), 0);
    return numbers;
}

void TestIntVector() {
    const vector<int> numbers = MakeTestVector();
    {
        LOG_DURATION("VECTOR");
        vector<int> numbers_copy = numbers;
        MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 1);
        ASSERT_EQUAL(numbers_copy, numbers);
    }
//    {
//        vector<int> numbers_copy = numbers;
//        MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 3);
//        ASSERT_EQUAL(numbers_copy, vector<int>({0, 3, 6, 9, 4, 8, 5, 2, 7, 1}));
//    }
}

// Это специальный тип, который поможет вам убедиться, что ваша реализация
// функции MakeJosephusPermutation не выполняет копирование объектов.
// Сейчас вы, возможно, не понимаете как он устроен, однако мы расскажем,
// почему он устроен именно так, далее в блоке про move-семантику —
// в видео «Некопируемые типы»

using NoncopyableInt = list<int>;

//struct NoncopyableInt {
//    int value;
//
//    NoncopyableInt(const NoncopyableInt &) = delete;
//
//    NoncopyableInt &operator=(const NoncopyableInt &) = delete;
//
//    NoncopyableInt(NoncopyableInt &&) = default;
//
//    NoncopyableInt &operator=(NoncopyableInt &&) = default;
//};
//
//
//bool operator==(const NoncopyableInt &lhs, const NoncopyableInt &rhs) {
//    return lhs.value == rhs.value;
//}
//
//ostream &operator<<(ostream &os, const NoncopyableInt &v) {
//    return os << v.value;
//}

void TestAvoidsCopying() {
    vector<NoncopyableInt> numbers;
    numbers.push_back({1});
    numbers.push_back({2});
    numbers.push_back({3});
    numbers.push_back({4});
    numbers.push_back({5});

    MakeJosephusPermutation(begin(numbers), end(numbers), 2);

    vector<NoncopyableInt> expected;
    expected.push_back({1});
    expected.push_back({3});
    expected.push_back({5});
    expected.push_back({4});
    expected.push_back({2});

//    ASSERT_EQUAL(numbers, expected);
}

list<int> MakeTestList() {
    list<int> numbers(100000);
    iota(begin(numbers), end(numbers), 0);
    return numbers;
}

void TestIntList() {
    const list<int> numbers = MakeTestList();
    {
        LOG_DURATION("LIST");
        list<int> numbers_copy = numbers;
        MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 1);
//        ASSERT_EQUAL(numbers_copy, numbers);
    }
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestIntVector);
    RUN_TEST(tr, TestAvoidsCopying);
    RUN_TEST(tr, TestIntList);
    return 0;
}
