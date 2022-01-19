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
    string right_part = to_string(x);
    int number;
    char prev_operation = '*';
    char cur_operation;
    string left_part;
    map<char, int> operations = {{'*', 1},
                                 {'/', 1},
                                 {'+', 0},
                                 {'-', 0}};
    while (n--){
        cin >> cur_operation;
        cin >> number;
        if (operations[cur_operation] > operations[prev_operation]){
            right_part.push_back(')');
            right_part.push_back(' ');
            right_part.push_back(cur_operation);
            right_part.push_back(' ');
            right_part += to_string(number);
            left_part.push_back('(');
        } else {
            right_part.push_back(' ');
            right_part.push_back(cur_operation);
            right_part.push_back(' ');
            right_part += to_string(number);
        }
        prev_operation = cur_operation;
    }
    cout << left_part + right_part << '\n';
    return 0;
}
