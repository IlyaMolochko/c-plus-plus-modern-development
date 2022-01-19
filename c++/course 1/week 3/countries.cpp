#include <iostream>
#include <map>

using namespace std;

int main() {
    int q;
    cin >> q;
    map<string, string> capitals;
    for (int i = 0; i < q; ++i) {
        string operation;
        cin >> operation;
        if (operation == "CHANGE_CAPITAL") {
            string country, new_capital;
            cin >> country >> new_capital;
            if (capitals.count(country) == 0) {
                cout << "Introduce new country " << country << " with capital " << new_capital << '\n';
            } else {
                string &old_capital = capitals[country];
                if (old_capital == new_capital) {
                    cout << "Country " << country << " hasn't changed its capital" << '\n';
                } else {
                    cout << "Country " << country << " has changed its capital from " << old_capital << " to "
                         << new_capital << '\n';
                }
            }
            capitals[country] = new_capital;
        } else if (operation == "RENAME") {
            string old_country_name, new_country_name;
            cin >> old_country_name >> new_country_name;
            if (old_country_name == new_country_name or capitals.count(old_country_name) == 0 or
                capitals.count(new_country_name) == 1) {
                cout << "Incorrect rename, skip" << '\n';
            } else {
                cout << "Country " << old_country_name << " with capital " << capitals[old_country_name] <<
                     " has been renamed to " << new_country_name << '\n';
                capitals[new_country_name] = capitals[old_country_name];
                capitals.erase(old_country_name);
            }
        } else if (operation == "ABOUT") {
            string country;
            cin >> country;
            if (capitals.count(country) == 0) {
                cout << "Country " << country << " doesn't exist" << '\n';
            } else {
                cout << "Country " << country << " has capital " << capitals[country] << '\n';
            }
        } else if (operation == "DUMP") {
            if (capitals.empty()) {
                cout << "There are no countries in the world" << '\n';
            } else {
                for (const auto &[country, capital] : capitals) {
                    cout << country << "/" << capital << " ";
                }
                cout << '\n';
            }
        }
    }
    return 0;
}
