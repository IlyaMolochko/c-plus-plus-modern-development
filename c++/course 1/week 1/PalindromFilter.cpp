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

vector<string> PalindromFilter(vector<string> &v, int minLength){
	vector<string> answ;
	for (auto &s: v){
		if (IsPalindrom(s) and s.size() >= minLength){
			answ.push_back(s);
		}
	}
	return answ;
}