#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");
    string s;
    if (input){
        while (getline(input, s)){
            output << s << '\n';
        }
    }
    return 0;
}
