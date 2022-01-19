#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main() {
    ifstream input("input.txt");
    double number;
    if (input){
        cout << fixed << setprecision(3);
        while (input >> number){
            cout << number << '\n';
        }
    }
    return 0;
}
