#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main() {
    ifstream input("input.txt");
    int n, m, number;
    input >> n >> m;
    if (input){

        for (int i = 0; i < n; ++i){
            for (int j = 0; j < m; ++j){
                input >> number;
                cout << setw(10) << number;
                if (j != m - 1){
                    input.ignore(1);
                    cout << ' ';
                }
            }
            if (i != n - 1){
                cout << '\n';
            }
        }
    }
    return 0;
}
