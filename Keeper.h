#ifndef LAB1_KEEPER_H
#define LAB1_KEEPER_H

#pragma once
#include "Base.h"
#include <string>

class Keeper {
private:
    Base** items;
    int count;
    void clear();

public:
    Keeper();
    Keeper(const Keeper& other);
    Keeper& operator=(const Keeper& other);
    ~Keeper();

    void add(Base* obj);
    void remove(int idx);
    int size() const;
    Base* operator[](int idx) const;

    void printAll(std::ostream& os) const;
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};

#endif //LAB1_KEEPER_H