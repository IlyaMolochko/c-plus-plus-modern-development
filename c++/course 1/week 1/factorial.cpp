#include <iostream>

using namespace std;

int Factorial(int n){
	int answ = 1;
	for (int i = 1; i <= n; ++i){
		answ *= i;
	}
	return answ;
}

int main(){
	int n;
	cin >> n;
	cout << Factorial(n) << '\n';
	return 0;
}