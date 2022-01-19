#include "test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end){
    if (range_end - range_begin < 3){
        return;
    }
    vector<typename RandomIt::value_type> elements(make_move_iterator(range_begin),
                                                   make_move_iterator(range_end));
    RandomIt first_end = elements.begin() + (elements.end() - elements.begin()) / 3;
    RandomIt second_end = elements.begin() + 2 * (elements.end() - elements.begin()) / 3;
    MergeSort(elements.begin(), first_end);
    MergeSort(first_end, second_end);
    MergeSort(second_end, elements.end());

    vector<typename RandomIt::value_type> tmp;
    merge(make_move_iterator(elements.begin()),
          make_move_iterator(first_end),
          make_move_iterator(first_end),
          make_move_iterator(second_end), back_inserter(tmp));
    merge(make_move_iterator(tmp.begin()),
          make_move_iterator(tmp.end()),
          make_move_iterator(second_end),
          make_move_iterator(elements.end()),
          range_begin);
}


void TestIntVector() {
    vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
    MergeSort(begin(numbers), end(numbers));
    ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestIntVector);
    return 0;
}