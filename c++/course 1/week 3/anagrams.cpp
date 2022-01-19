#include <iostream>
#include <map>

using namespace std;

void BuildCharCounters(string &s, map<char, int> &dict){
	for (auto c : s){
		++dict[c];
	}
}

int main()
{
	int n;
	cin >> n;
	string first_word;
	string second_word;
	for (int i = 0; i < n; ++i){
		cin >> first_word;
		cin >> second_word;
		map<char, int> first_dict;
		map<char, int> second_dict;
		BuildCharCounters(first_word, first_dict);
		BuildCharCounters(second_word, second_dict);
		cout << (first_dict == second_dict ? "YES" : "NO") << '\n'; 
	}
	return 0;
}