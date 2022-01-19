#include <iostream>
#include <iomanip>
#include <map>
#include <set>
#include <sstream>

using namespace std;

class Date {
public:
    Date(int new_year, int new_month, int new_day) {
        year = new_year;
        if (new_month > 12 or new_month < 1) {
            throw runtime_error("Month value is invalid: " + to_string(new_month));
        }
        month = new_month;
        if (new_day > 31 or new_day < 1) {
            throw runtime_error("Day value is invalid: " + to_string(new_day));
        }
        day = new_day;
    }

    int GetYear() const {
        return year;
    }

    int GetMonth() const {
        return month;
    }

    int GetDay() const {
        return day;
    }

private:
    int year;
    int month;
    int day;
};

bool operator<(const Date &lhs, const Date &rhs) {
    if (lhs.GetYear() == rhs.GetYear()){
        if (lhs.GetMonth() == rhs.GetMonth()){
            return lhs.GetDay() < rhs.GetDay();
        }
        return lhs.GetMonth() < rhs.GetMonth();
    }
    return lhs.GetYear() < rhs.GetYear();
}

ostream& operator<<(ostream& os, const Date &date){
    os << setw(4) << setfill('0') << date.GetYear();
    os << '-';
    os << setw(2) << setfill('0') << date.GetMonth();
    os << '-';
    os << setw(2) << setfill('0') << date.GetDay();
    return os;
}

class Database {
public:
    void AddEvent(const Date &date, const string &event) {
        data[date].insert(event);
    }

    bool DeleteEvent(const Date &date, const string &event) {
        if (data.count(date) and data[date].count(event)) {
            data[date].erase(event);
            return true;
        }
        return false;
    }

    int DeleteDate(const Date &date) {
        if (data.count(date)) {
            int size = data[date].size();
            data.erase(date);
            return size;
        }
        return 0;
    }

    set<string> Find(const Date &date) const {
        if (data.count(date)) {
            return data.at(date);
        }
        return {};
    }

    void Print() const {
        for (const auto &[date, events] : data) {
            for (const auto &event : events) {
                cout << date << ' ' << event << '\n';
            }
        }
    }

private:
    map<Date, set<string>> data;
};

void EnsureNextSymbolAndSkip(stringstream &stream) {
    if (stream.peek() != '-') {
        stringstream ss;
        ss << "expected - , but has: " << char(stream.peek());
        throw runtime_error(ss.str());
    }
    stream.ignore(1);
}

Date ParseDate(const string &date) {
    stringstream ss(date);
    int year;
    int month;
    int day = -2147483648;
    string value;
    try {
        if (ss.eof()) {
            throw runtime_error("Wrong date format: " + date);
        }
        ss >> year;
        EnsureNextSymbolAndSkip(ss);
        ss >> month;
        EnsureNextSymbolAndSkip(ss);
        ss >> day;
//        day = stoi(value);
//        cerr << value.size() << '\n';
if (!ss.eof() or day == -2147483648) {
            throw runtime_error("Wrong date format: " + date);
        }

    } catch (exception &e) {
        throw runtime_error("Wrong date format: " + date);
    }
    return {year, month, day};
}

int main() {
    try {
        Database db;

        string command;

        while (getline(cin, command)) {
            stringstream ss(command);
            string operation;
            ss >> operation;
            if (operation == "Add") {
                string date_str;
                string event;
                ss >> date_str >> event;
                Date date = ParseDate(date_str);
                db.AddEvent(date, event);
            } else if (operation == "Del") {
                string date_str;
                ss >> date_str;
                Date date = ParseDate(date_str);
                string event;
                if (!ss.eof()) {
                    ss >> event;
                    if (db.DeleteEvent(date, event)){
                        cout << "Deleted successfully" << '\n';
                    } else {
                        cout << "Event not found" << '\n';
                    }
                } else {
                    cout << "Deleted " << db.DeleteDate(date) << " events" << '\n';
                }

            } else if (operation == "Find") {
                string date_str;
                ss >> date_str;
                Date date = ParseDate(date_str);
                for (auto &event: db.Find(date)){
                    cout << event << '\n';
                }
            } else if (operation == "Print") {
                db.Print();
            } else if (operation.empty()){
                continue;
            }
            else {
                throw runtime_error("Unknown command: " + operation);
            }
        }
    } catch (exception &e) {
        cout << e.what() << '\n';
    }

    return 0;
}