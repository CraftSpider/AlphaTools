
#include "console.h"

namespace term {

std::string SET_ICON_TITLE(std::string name) {
    std::stringstream ss;
    ss << "\033]0;" << name << '\x07';
    return ss.str();
}

std::string SET_TITLE(std::string name) {
    std::stringstream ss;
    ss << "\033]2;" << name << '\x07';
    return ss.str();
}

std::string SCROLL_UP(ushort n) {
    std::stringstream ss;
    ss << "\033[" << n << "S";
    return ss.str();
}

std::string SCROLL_DOWN(ushort n) {
    std::stringstream ss;
    ss << "\033[" << n << "T";
    return ss.str();
}

namespace curs {

std::string UP(ushort n) {
    std::stringstream ss;
    ss << "\033[" << n << "A";
    return ss.str();
}

std::string DOWN(ushort n) {
    std::stringstream ss;
    ss << "\033[" << n << "B";
    return ss.str();
}

std::string FORWARD(ushort n) {
    std::stringstream ss;
    ss << "\033[" << n << "C";
    return ss.str();
}

std::string BACKWARD(ushort n) {
    std::stringstream ss;
    ss << "\033[" << n << "D";
    return ss.str();
}

std::string DOWN_LINE(ushort n) {
    std::stringstream ss;
    ss << "\033[" << n << "E";
    return ss.str();
}

std::string UP_LINE(ushort n) {
    std::stringstream ss;
    ss << "\033[" << n << "F";
    return ss.str();
}

std::string SET_HORIZONTAL(ushort n) {
    std::stringstream ss;
    ss << "\033[" << n << "G";
    return ss.str();
}

std::string SET_VERTICAL(ushort n) {
    std::stringstream ss;
    ss << "\033[" << n << "d";
    return ss.str();
}

std::string SET_POS(ushort x, ushort y) {
    std::stringstream ss;
    ss << "\033[" << y << ";" << x << "H";
    return ss.str();
}

}

namespace text {

std::string INSERT(ushort n) {
    std::stringstream ss;
    ss << "\033[" << n << "@";
    return ss.str();
}

std::string DELETE(ushort n) {
    std::stringstream ss;
    ss << "\033[" << n << "P";
    return ss.str();
}

std::string ERASE(ushort n) {
    std::stringstream ss;
    ss << "\033[" << n << "X";
    return ss.str();
}

std::string INSERT_LINE(ushort n) {
    std::stringstream ss;
    ss << "\033[" << n << "L";
    return ss.str();
}

std::string DELETE_LINE(ushort n) {
    std::stringstream ss;
    ss << "\033[" << n << "M";
    return ss.str();
}

std::string CLEAR(ushort option) {
    std::stringstream ss;
    ss << "\033[" << option << "J";
    return ss.str();
}

std::string CLEAR_LINE(ushort option) {
    std::stringstream ss;
    ss << "\033[" << option << "K";
    return ss.str();
}

}

}