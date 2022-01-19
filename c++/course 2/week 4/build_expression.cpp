#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;



int main() {
    int x;
    cin >> x;
    int n;
    cin >> n;
    string s(n, '(');
    s += to_string(x);
    int number;
    while (n--){
        char operation;
        cin >> operation;
        cin >> number;
        s.push_back(')');
        s.push_back(' ');
        s.push_back(operation);
        s.push_back(' ');
        s += to_string(number);
    }

    cout << s << '\n';
    return 0;
}
