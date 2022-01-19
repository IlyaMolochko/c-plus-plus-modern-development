#pragma once

#include <ostream>
#include <sstream>

class Date{
public:
    Date(const int &year, const int &month, const int &day);

    int GetYear() const;

    int GetMonth() const;

    int GetDay() const;

private:
    const int year_;
    const int month_;
    const int day_;
};

Date ParseDate(std::istream &is);

bool operator<(const Date &first_date, const Date &second_date);

bool operator<=(const Date &first_date, const Date &second_date);

bool operator>(const Date &first_date, const Date &second_date);

bool operator>=(const Date &first_date, const Date &second_date);

bool operator==(const Date &first_date, const Date &second_date);

bool operator!=(const Date &first_date, const Date &second_date);

std::ostream& operator<<(std::ostream &os, const Date &date);

