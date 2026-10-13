

#ifndef ШАБЛ_DATE_H
#define ШАБЛ_DATE_H


#pragma once
#include <string>

struct Date {
    int day;
    int month;
    int year;

    Date() : day(0), month(0), year(0) {}
    Date(int d, int m, int y) : day(d), month(m), year(y) {}

    std::string toString() const;
    bool isEmpty() const { return day == 0 && month == 0 && year == 0; }
};


#endif //ШАБЛ_DATE_H