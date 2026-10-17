#include "Keeper.h"
#include "FamilyMember.h"
#include <iostream>
#include <limits>
#include <stdexcept>

static void printMenu() {
    std::cout << "\n===== МЕНЮ =====\n"
              << "1. Добавить члена семьи\n"
              << "2. Удалить члена семьи\n"
              << "3. Вывести всех\n"
              << "4. Изменить данные члена семьи\n"
              << "5. Сохранить в файл\n"
              << "6. Загрузить из файла\n"
              << "0. Выход\n"
              << "Выбор: ";
}

static int readInt() {
    int x;
    while (!(std::cin >> x)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Ошибка ввода, повторите: ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return x;
}

static std::string readLine(const std::string& prompt) {
    std::string s;
    std::cout << prompt;
    std::getline(std::cin, s);
    return s;
}

static Date readDate(const std::string& prompt) {
    std::cout << prompt << " (дд мм гггг, 0 0 0 — нет): ";
    int d, m, y;
    if (!(std::cin >> d >> m >> y))
        throw std::runtime_error("Ошибка ввода даты");
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return Date(d, m, y);
}

int main() {
#ifdef WIN64
    system("chcp 65001");
#endif
#ifdef WIN32
    system("chcp 65001");
#endif
    Keeper keeper;
    int choice = -1;
    while (choice != 0) {
        try {
            printMenu();
            choice = readInt();
            switch (choice) {
            case 1: {
                std::string fio = readLine("ФИО: ");
                Date birth = readDate("Дата рождения");
                Date death = readDate("Дата смерти");
                std::cout << "Возраст: ";
                int age = readInt();
                std::string spouse = readLine("Супруг(а): ");
                FamilyMember* m = new FamilyMember(fio, birth, death, age, spouse);
                std::cout << "Сколько родителей добавить? ";
                int pc = readInt();
                for (int i = 0; i < pc; ++i) m->addParent(readLine("  Родитель: "));
                std::cout << "Сколько детей добавить? ";
                int cc = readInt();
                for (int i = 0; i < cc; ++i) m->addChild(readLine("  Ребёнок: "));
                keeper.add(m);
                std::cout << "Добавлено.\n";
                break;
            }
            case 2: {
                if (keeper.size() == 0) { std::cout << "Пусто.\n"; break; }
                std::cout << "Индекс для удаления (0.." << keeper.size() - 1 << "): ";
                keeper.remove(readInt());
                std::cout << "Удалено.\n";
                break;
            }
            case 3:
                keeper.printAll(std::cout);
                break;
            case 4: {
                if (keeper.size() == 0) { std::cout << "Пусто.\n"; break; }
                std::cout << "Индекс (0.." << keeper.size() - 1 << "): ";
                int idx = readInt();
                FamilyMember* m = dynamic_cast<FamilyMember*>(keeper[idx]);
                if (!m) throw std::runtime_error("Объект не является FamilyMember");
                std::cout << "1-ФИО 2-Возраст 3-Супруг 4-Добавить родителя 5-Добавить ребёнка\n";
                int sub = readInt();
                if (sub == 1) m->setFio(readLine("Новое ФИО: "));
                else if (sub == 2) { std::cout << "Возраст: "; m->setAge(readInt()); }
                else if (sub == 3) m->setSpouse(readLine("Супруг(а): "));
                else if (sub == 4) m->addParent(readLine("Родитель: "));
                else if (sub == 5) m->addChild(readLine("Ребёнок: "));
                else std::cout << "Неизвестное действие.\n";
                break;
            }
            case 5:
                keeper.saveToFile(readLine("Имя файла: "));
                std::cout << "Сохранено.\n";
                break;
            case 6:
                keeper.loadFromFile(readLine("Имя файла: "));
                std::cout << "Загружено.\n";
                break;
            case 0:
                std::cout << "Выход.\n";
                break;
            default:
                std::cout << "Неверный пункт меню.\n";
            }
        } catch (const std::exception& e) {
            std::cout << "ИСКЛЮЧЕНИЕ: " << e.what() << "\n";
        }
    }
    return 0;
}