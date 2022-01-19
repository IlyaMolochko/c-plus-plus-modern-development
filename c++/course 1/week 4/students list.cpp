#include <iostream>
#include <vector>

using namespace std;

struct Student{
    string first_name;
    string last_name;
    int day;
    int month;
    int year;
};

int main() {
    int n;
    cin >> n;
    vector<Student> students(n);
    for (auto &student : students){
        cin >> student.first_name >> student.last_name
        >> student.day >> student.month >> student.year;
    }
    int m;
    cin >> m;
    string query;
    int k;
    for (int i = 0; i < m; ++i){
        cin >> query >> k;
        if (query == "name" and k > 0 and k <= n){
            cout << students[k - 1].first_name << ' '
            << students[k - 1].last_name << '\n';
        } else if (query == "date" and k > 0 and k <= n){
            cout << students[k - 1].day << '.'
            << students[k - 1].month << '.'
            << students[k - 1].year << '\n';
        } else {
            cout << "bad request" << '\n';
        }
    }
    return 0;
}
