#pragma once

#include "date.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>

struct Entry{
    Date date;
    std::string event;
};

std::ostream& operator<<(std::ostream &os, const Entry &entry);

class Database{
public:
    void Add(const Date &date, const std::string &event);

    void Print(std::ostream &os) const;

    template<typename Predicate>
    int RemoveIf(Predicate predicate){
        int count = 0;
        std::vector<Date> to_delete;
        for (auto &[date, events] : events_per_date_){
            auto it = std::stable_partition(events.begin(), events.end(), [predicate, date = date](const std::string &event){
                return !predicate(date, event);
            });

            count += events.end() - it;
            for (auto iter = it; iter != events.end(); ++iter){
                events_per_date_set_[date].erase(*iter);
            }
            events.erase(it, events.end());

            if (events.empty()){
                to_delete.push_back(date);
            }
        }
        for (auto &date : to_delete){
            events_per_date_.erase(date);
            events_per_date_set_.erase(date);
        }
        return count;
    }

    template<typename Predicate>
    std::vector<Entry> FindIf(Predicate predicate) const {
        std::vector<Entry> entries;
        for (const auto &[date, events] : events_per_date_){
            for (const auto &event : events){
                if (predicate(date, event)){
                    entries.push_back({date, event});
                }
            }
        }
        return entries;
    }

    Entry Last(const Date &date) const;

private:
    std::map<Date, std::vector<std::string>> events_per_date_;
    std::map<Date, std::set<std::string>> events_per_date_set_;
};
