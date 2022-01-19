#include <iostream>

void Reverse(vector<int> &v){
	for (int i = 0; i < v.size() / 2; ++i){
		swap(v[i], v[v.size() - i - 1]);
	}
}