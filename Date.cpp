#include "Date.h"
#include <sstream>

std::string Date::toString() const {
    if (isEmpty()) return "—";
    std::ostringstream os;
    os << day << "." << month << "." << year;
    return os.str();
}