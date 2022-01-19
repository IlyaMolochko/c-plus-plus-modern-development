#include <iostream>
#include <vector>

using namespace std;


int main(){
	vector<int> months_length = {31, 28, 31, 30,
						31, 30, 31, 31,
						30, 31, 30, 31};
	int q;
	int month = 0;
	int prev_month;
	int month_length;
	int prev_month_length;
	vector<vector<string>> days_tasks(months_length[month]);
	string operation;

	cin >> q;
	
	for (int i = 0; i < q; ++i){
		cin >> operation;
		if (operation == "ADD"){
			int day;
			string task;
			cin >> day >> task;
			days_tasks[day - 1].push_back(task);
		} else if (operation == "NEXT"){
			prev_month = month;
			month = (month + 1) % months_length.size();
			month_length = months_length[month];
			prev_month_length = months_length[prev_month];
			if (month_length < prev_month_length){
				vector<string> &last_day_tasks = days_tasks[month_length - 1];
				for (int day = month_length; day < prev_month_length; ++day){
					last_day_tasks.insert(last_day_tasks.end(), 
						days_tasks[day].begin(),days_tasks[day].end());
				}
			}
			days_tasks.resize(month_length);
		} else {
			int day;
			cin >> day;
			--day;
			cout << days_tasks[day].size() << ' ';
			for (auto &task: days_tasks[day]){
				cout << task << ' ';
			}
			cout << '\n';
		}
	}
	return 0;
}