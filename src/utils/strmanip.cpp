
#include "utils/strmanip.h"

#include <sstream>
#include <cctype>
#include "utils/bytes.h"

namespace util {

std::string reverse(const std::string& str) {
    std::string out;
    for (auto i : str) {
        out.insert(out.begin(), i);
    }
    return out;
}

bool starts_with(const std::string &val, const std::string &start) {
    if (start.size() > val.size()) return false;
    return !val.compare(0, start.length(), start);
}

bool ends_with(const std::string &val, const std::string &end) {
    if (end.size() > val.size()) return false;
    return !val.compare(val.length() - end.length(), end.length(), end);
}

std::string to_uppercase(const std::string& str) {
    std::stringstream out;
    for (auto c : str) {
        out << (char)std::toupper(c);
    }
    return out.str();
}

std::string to_lowercase(const std::string& str) {
    std::stringstream out;
    for (auto c : str) {
        out << (char)std::tolower(c);
    }
    return out.str();
}

}
