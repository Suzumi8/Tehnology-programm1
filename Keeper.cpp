#include "Keeper.h"
#include "FamilyMember.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

Keeper::Keeper() : items(nullptr), count(0) {
    std::cout << "[Keeper] конструктор по умолчанию\n";
}

void Keeper::clear() {
    for (int i = 0; i < count; ++i) delete items[i];
    delete[] items;
    items = nullptr; count = 0;
}

Keeper::Keeper(const Keeper& o) : items(nullptr), count(0) {
    std::cout << "[Keeper] конструктор копирования\n";
    count = o.count;
    items = count ? new Base*[count] : nullptr;
    for (int i = 0; i < count; ++i)
        items[i] = new FamilyMember(*static_cast<FamilyMember*>(o.items[i]));
}

Keeper& Keeper::operator=(const Keeper& o) {
    if (this != &o) {
        clear();
        count = o.count;
        items = count ? new Base*[count] : nullptr;
        for (int i = 0; i < count; ++i)
            items[i] = new FamilyMember(*static_cast<FamilyMember*>(o.items[i]));
    }
    return *this;
}

Keeper::~Keeper() {
    std::cout << "[Keeper] деструктор\n";
    clear();
}

void Keeper::add(Base* obj) {
    if (!obj) throw std::invalid_argument("Попытка добавить null-объект");
    Base** tmp = new Base*[count + 1];
    for (int i = 0; i < count; ++i) tmp[i] = items[i];
    tmp[count] = obj;
    delete[] items;
    items = tmp;
    ++count;
}

void Keeper::remove(int idx) {
    if (idx < 0 || idx >= count)
        throw std::out_of_range("Неверный индекс при удалении");
    delete items[idx];
    Base** tmp = count > 1 ? new Base*[count - 1] : nullptr;
    for (int i = 0, j = 0; i < count; ++i) if (i != idx) tmp[j++] = items[i];
    delete[] items;
    items = tmp;
    --count;
}

int Keeper::size() const { return count; }

Base* Keeper::operator[](int idx) const {
    if (idx < 0 || idx >= count)
        throw std::out_of_range("Индекс вне диапазона контейнера");
    return items[idx];
}

void Keeper::printAll(std::ostream& os) const {
    if (count == 0) { os << "Контейнер пуст.\n"; return; }
    for (int i = 0; i < count; ++i)
        os << "--- #" << i << " ---\n" << *items[i] << "\n";
}

void Keeper::saveToFile(const std::string& filename) const {
    std::ofstream f(filename);
    if (!f) throw std::runtime_error("Не удалось открыть файл для записи: " + filename);
    f << count << "\n";
    for (int i = 0; i < count; ++i) items[i]->save(f);
    f.close();
    if (!f) throw std::runtime_error("Ошибка записи в файл: " + filename);
}

void Keeper::loadFromFile(const std::string& filename) {
    std::ifstream f(filename);
    if (!f) throw std::runtime_error("Не удалось открыть файл для чтения: " + filename);
    int n = 0;
    if (!(f >> n))
        throw std::runtime_error("Ошибка чтения количества объектов из файла");
    if (n < 0)
        throw std::runtime_error("Некорректное количество объектов в файле");
    f.ignore();
    clear();
    for (int i = 0; i < n; ++i) {
        std::string type;
        std::getline(f, type);
        if (type != "FamilyMember")
            throw std::runtime_error("Неизвестный тип объекта: " + type);
        FamilyMember* m = new FamilyMember();
        m->load(f);
        add(m);
    }
}