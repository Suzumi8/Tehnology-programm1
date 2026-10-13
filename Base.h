#pragma once
#include <iostream>
#include <string>

class Base {
public:
    Base() { std::cout << "[Base] конструктор по умолчанию\n"; }
    Base(const Base&) { std::cout << "[Base] конструктор копирования\n"; }
    virtual ~Base() { std::cout << "[Base] деструктор\n"; }

    virtual void print(std::ostream& os) const = 0;
    virtual void save(std::ostream& os) const = 0;
    virtual void load(std::istream& is) = 0;
    virtual std::string getType() const = 0;

    friend std::ostream& operator<<(std::ostream& os, const Base& b) {
        b.print(os);
        return os;
    }
};

#ifndef LAB1_BASE_H
#define LAB1_BASE_H

#endif //LAB1_BASE_H