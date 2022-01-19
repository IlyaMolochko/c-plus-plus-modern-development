#include "database.h"

std::ostream& operator<<(std::ostream &os, const Entry &entry){
    os << entry.date << ' ' << entry.event;
    return os;
}

void Database::Add(const Date &date, const std::string &event) {
    if (events_per_date_set_[date].count(event) == 0){
        events_per_date_set_[date].insert(event);
        events_per_date_[date].push_back(event);
    }
}

void Database::Print(std::ostream &os) const {
    for (auto &[date, events] : events_per_date_){
        for (auto &event : events){
            os << date << ' ' << event << '\n';
        }
    }
}

Entry Database::Last(const Date &date) const {
    auto it = events_per_date_.upper_bound(date);
    if (it == events_per_date_.begin()){
        throw std::invalid_argument("No entries");
    }
    --it;
    return {it->first, *it->second.rbegin()};
}


