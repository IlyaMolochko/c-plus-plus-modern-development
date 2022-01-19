#include "date.h"
#include <iomanip>
#include <tuple>

Date::Date(const int &year,
           const int &month,
           const int &day) :
        year_(year),
        month_(month),
        day_(day) {}

int Date::GetYear() const {
    return year_;
}

int Date::GetMonth() const {
    return month_;
}

int Date::GetDay() const {
    return day_;
}

Date ParseDate(std::istream &is){
    int year;
    int month;
    int day;
    is >> year;
    is.ignore();
    is >> month;
    is.ignore();
    is >> day;
    return {year, month, day};
}

bool operator<(const Date &first_date, const Date &second_date) {
    return std::tuple(first_date.GetYear(), first_date.GetMonth(), first_date.GetDay())
           < std::tuple(second_date.GetYear(), second_date.GetMonth(), second_date.GetDay());
}

bool operator<=(const Date &first_date, const Date &second_date) {
    return std::tuple(first_date.GetYear(), first_date.GetMonth(), first_date.GetDay())
           <= std::tuple(second_date.GetYear(), second_date.GetMonth(), second_date.GetDay());
}

bool operator>(const Date &first_date, const Date &second_date) {
    return std::tuple(first_date.GetYear(), first_date.GetMonth(), first_date.GetDay())
           > std::tuple(second_date.GetYear(), second_date.GetMonth(), second_date.GetDay());
}

bool operator>=(const Date &first_date, const Date &second_date) {
    return std::tuple(first_date.GetYear(), first_date.GetMonth(), first_date.GetDay())
           >= std::tuple(second_date.GetYear(), second_date.GetMonth(), second_date.GetDay());
}

bool operator==(const Date &first_date, const Date &second_date) {
    return std::tuple(first_date.GetYear(), first_date.GetMonth(), first_date.GetDay())
           == std::tuple(second_date.GetYear(), second_date.GetMonth(), second_date.GetDay());
}

bool operator!=(const Date &first_date, const Date &second_date) {
    return std::tuple(first_date.GetYear(), first_date.GetMonth(), first_date.GetDay())
           != std::tuple(second_date.GetYear(), second_date.GetMonth(), second_date.GetDay());
}

std::ostream& operator<<(std::ostream &os, const Date &date) {
    os << std::setw(4) << std::setfill('0')
    << date.GetYear() << "-"
    << std::setw(2) << std::setfill('0')
    << date.GetMonth() << "-"
    << std::setw(2) << std::setfill('0')
    << date.GetDay();
    return os;
}
