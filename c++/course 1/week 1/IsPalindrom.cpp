#include <iostream>

using namespace std;

bool IsPalindrom(string &s){
	int n = s.size();
	for (int i = 0; i < n / 2; ++i){
		if (s[i] != s[n - i - 1]){
			return false;
		}
	}
	return true;
}

int main(){
	string s;
	cin >> s;
	cout << IsPalindrom(s) << '\n';
	return 0;
}