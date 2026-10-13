#ifndef LAB1_FAMILYMEMBER_H
#define LAB1_FAMILYMEMBER_H

#pragma once
#include "Base.h"
#include "Date.h"

class FamilyMember : public Base {
private:
    std::string fio;
    Date birth;
    Date death;      // пустая, если жив
    int age;

    // динамические массивы строк (ручное управление памятью)
    std::string* parents;
    int parentsCount;
    std::string* children;
    int childrenCount;
    std::string spouse;

    void copyFrom(const FamilyMember& other);
    void freeMemory();

public:
    FamilyMember();
    FamilyMember(const std::string& fio, const Date& birth, const Date& death,
                 int age, const std::string& spouse);
    FamilyMember(const FamilyMember& other);
    FamilyMember& operator=(const FamilyMember& other);
    ~FamilyMember() override;

    // set/get
    void setFio(const std::string& v);
    std::string getFio() const;
    void setBirth(const Date& d);
    Date getBirth() const;
    void setDeath(const Date& d);
    Date getDeath() const;
    void setAge(int a);
    int getAge() const;
    void setSpouse(const std::string& s);
    std::string getSpouse() const;

    void addParent(const std::string& p);
    void addChild(const std::string& c);
    void removeParent(int idx);
    void removeChild(int idx);
    int getParentsCount() const;
    int getChildrenCount() const;
    std::string getParent(int idx) const;
    std::string getChild(int idx) const;

    void print(std::ostream& os) const override;
    void save(std::ostream& os) const override;
    void load(std::istream& is) override;
    std::string getType() const override { return "FamilyMember"; }
};

#endif //LAB1_FAMILYMEMBER_H