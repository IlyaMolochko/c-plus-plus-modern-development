#include <iostream>
#include <iomanip>
#include <map>
#include <set>
#include <sstream>
#include <vector>

using namespace std;

template<typename Key, typename Value>
Value& GetRefStrict(map<Key, Value> &mp, Key k){
    if (mp.count(k) == 0){
        throw runtime_error("");
    }
    return mp.at(k);
}


int main() {

    map<int, string> m = {{0, "value"}};
    string& item = GetRefStrict(m, 0);
    item = "newvalue";
    cout << m[0] << endl; // выведет newvalue

    return 0;
}