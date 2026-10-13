#include "FamilyMember.h"
#include <sstream>
#include <limits>
#include <stdexcept>

FamilyMember::FamilyMember()
    : Base(), fio(""), birth(), death(), age(0),
      parents(nullptr), parentsCount(0), children(nullptr), childrenCount(0),
      spouse("") {
    std::cout << "[FamilyMember] конструктор по умолчанию\n";
}

FamilyMember::FamilyMember(const std::string& fio_, const Date& birth_,
                           const Date& death_, int age_, const std::string& spouse_)
    : Base(), fio(fio_), birth(birth_), death(death_), age(age_),
      parents(nullptr), parentsCount(0), children(nullptr), childrenCount(0),
      spouse(spouse_) {
    std::cout << "[FamilyMember] конструктор с параметрами\n";
}

void FamilyMember::copyFrom(const FamilyMember& o) {
    fio = o.fio; birth = o.birth; death = o.death; age = o.age; spouse = o.spouse;

    parentsCount = o.parentsCount;
    parents = parentsCount ? new std::string[parentsCount] : nullptr;
    for (int i = 0; i < parentsCount; ++i) parents[i] = o.parents[i];

    childrenCount = o.childrenCount;
    children = childrenCount ? new std::string[childrenCount] : nullptr;
    for (int i = 0; i < childrenCount; ++i) children[i] = o.children[i];
}

void FamilyMember::freeMemory() {
    delete[] parents; parents = nullptr; parentsCount = 0;
    delete[] children; children = nullptr; childrenCount = 0;
}

FamilyMember::FamilyMember(const FamilyMember& o) : Base(o) {
    std::cout << "[FamilyMember] конструктор копирования\n";
    copyFrom(o);
}

FamilyMember& FamilyMember::operator=(const FamilyMember& o) {
    if (this != &o) {
        freeMemory();
        copyFrom(o);
    }
    return *this;
}

FamilyMember::~FamilyMember() {
    std::cout << "[FamilyMember] деструктор (" << fio << ")\n";
    freeMemory();
}

void FamilyMember::setFio(const std::string& v) { fio = v; }
std::string FamilyMember::getFio() const { return fio; }
void FamilyMember::setBirth(const Date& d) { birth = d; }
Date FamilyMember::getBirth() const { return birth; }
void FamilyMember::setDeath(const Date& d) { death = d; }
Date FamilyMember::getDeath() const { return death; }
void FamilyMember::setAge(int a) { age = a; }
int FamilyMember::getAge() const { return age; }
void FamilyMember::setSpouse(const std::string& s) { spouse = s; }
std::string FamilyMember::getSpouse() const { return spouse; }

void FamilyMember::addParent(const std::string& p) {
    std::string* tmp = new std::string[parentsCount + 1];
    for (int i = 0; i < parentsCount; ++i) tmp[i] = parents[i];
    tmp[parentsCount] = p;
    delete[] parents;
    parents = tmp;
    ++parentsCount;
}

void FamilyMember::addChild(const std::string& c) {
    std::string* tmp = new std::string[childrenCount + 1];
    for (int i = 0; i < childrenCount; ++i) tmp[i] = children[i];
    tmp[childrenCount] = c;
    delete[] children;
    children = tmp;
    ++childrenCount;
}

void FamilyMember::removeParent(int idx) {
    if (idx < 0 || idx >= parentsCount)
        throw std::out_of_range("Неверный индекс родителя");
    std::string* tmp = parentsCount > 1 ? new std::string[parentsCount - 1] : nullptr;
    for (int i = 0, j = 0; i < parentsCount; ++i) if (i != idx) tmp[j++] = parents[i];
    delete[] parents; parents = tmp; --parentsCount;
}

void FamilyMember::removeChild(int idx) {
    if (idx < 0 || idx >= childrenCount)
        throw std::out_of_range("Неверный индекс ребёнка");
    std::string* tmp = childrenCount > 1 ? new std::string[childrenCount - 1] : nullptr;
    for (int i = 0, j = 0; i < childrenCount; ++i) if (i != idx) tmp[j++] = children[i];
    delete[] children; children = tmp; --childrenCount;
}

int FamilyMember::getParentsCount() const { return parentsCount; }
int FamilyMember::getChildrenCount() const { return childrenCount; }

std::string FamilyMember::getParent(int idx) const {
    if (idx < 0 || idx >= parentsCount)
        throw std::out_of_range("Неверный индекс родителя");
    return parents[idx];
}
std::string FamilyMember::getChild(int idx) const {
    if (idx < 0 || idx >= childrenCount)
        throw std::out_of_range("Неверный индекс ребёнка");
    return children[idx];
}

void FamilyMember::print(std::ostream& os) const {
    os << "ФИО: " << fio << "\n"
       << "Дата рождения: " << birth.toString() << "\n"
       << "Дата смерти: " << death.toString() << "\n"
       << "Возраст: " << age << "\n"
       << "Супруг(а): " << (spouse.empty() ? "—" : spouse) << "\n"
       << "Родители (" << parentsCount << "): ";
    for (int i = 0; i < parentsCount; ++i) os << parents[i] << (i + 1 < parentsCount ? ", " : "");
    os << "\nДети (" << childrenCount << "): ";
    for (int i = 0; i < childrenCount; ++i) os << children[i] << (i + 1 < childrenCount ? ", " : "");
    os << "\n";
}

void FamilyMember::save(std::ostream& os) const {
    os << "FamilyMember\n";
    os << fio << "\n"
       << birth.day << " " << birth.month << " " << birth.year << "\n"
       << death.day << " " << death.month << " " << death.year << "\n"
       << age << "\n"
       << spouse << "\n"
       << parentsCount << "\n";
    for (int i = 0; i < parentsCount; ++i) os << parents[i] << "\n";
    os << childrenCount << "\n";
    for (int i = 0; i < childrenCount; ++i) os << children[i] << "\n";
}

void FamilyMember::load(std::istream& is) {
    std::getline(is, fio);
    if (!(is >> birth.day >> birth.month >> birth.year))
        throw std::runtime_error("Ошибка чтения даты рождения из файла");
    if (!(is >> death.day >> death.month >> death.year))
        throw std::runtime_error("Ошибка чтения даты смерти из файла");
    if (!(is >> age))
        throw std::runtime_error("Ошибка чтения возраста из файла");
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(is, spouse);

    freeMemory();
    if (!(is >> parentsCount))
        throw std::runtime_error("Ошибка чтения количества родителей из файла");
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (parentsCount > 0) {
        parents = new std::string[parentsCount];
        for (int i = 0; i < parentsCount; ++i) std::getline(is, parents[i]);
    }
    if (!(is >> childrenCount))
        throw std::runtime_error("Ошибка чтения количества детей из файла");
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (childrenCount > 0) {
        children = new std::string[childrenCount];
        for (int i = 0; i < childrenCount; ++i) std::getline(is, children[i]);
    }
}