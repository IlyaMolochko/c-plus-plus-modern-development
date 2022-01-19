vector<int> Reversed(const vector<int> &v){
	vector<int> answ(v.size());
	for (int i = 0; i < v.size(); ++i){
		answ[v.size() - i - 1] = v[i];
	}
	return answ;
}