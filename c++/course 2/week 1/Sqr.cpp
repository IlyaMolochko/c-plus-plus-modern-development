#include <iostream>
#include <iomanip>
#include <map>
#include <set>
#include <sstream>
#include <vector>

using namespace std;

template<typename T> T Sqr(T x);
template<typename T> vector<T> Sqr(vector<T> v);
template<typename First, typename Second>
pair<First, Second> Sqr(pair<First, Second> p);
template<typename Key,typename Value>
map<Key, Value> Sqr(map<Key, Value> mp);


template<typename T>
T Sqr(T x){
    return x * x;
}

template<typename T>
vector<T> Sqr(vector<T> v){
    vector<T> result(v.begin(), v.end());
    for (auto &item : result){
        item = Sqr(item);
    }
    return result;
}

template<typename First, typename Second>
pair<First, Second> Sqr(pair<First, Second> p){
    return {Sqr(p.first), Sqr(p.second)};
}

template<typename Key,typename Value>
map<Key, Value> Sqr(map<Key, Value> mp){
    map<Key, Value> result = mp;
    for (auto &[key, value] : result){
        value = Sqr(value);
    }
    return result;
}

//int main() {
//
//    vector<int> v = {1, 2, 3};
//    cout << "vector:";
//    for (int x : Sqr(v)) {
//        cout << ' ' << x;
//    }
//    cout << endl;
//
//    map<int, pair<int, int>> map_of_pairs = {
//            {4, {2, 2}},
//            {7, {4, 3}}
//    };
//    cout << "map of pairs:" << endl;
//    for (const auto& x : Sqr(map_of_pairs)) {
//        cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
//    }
//
//    return 0;
//}