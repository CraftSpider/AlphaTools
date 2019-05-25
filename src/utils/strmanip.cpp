
#include "utils/strmanip.h"

#include <sstream>
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

std::string to_uppercase(std::string str) {
    std::stringstream out;
    for (auto c : str) {
        out << (char)std::toupper(c);
    }
    return out.str();
}

std::string to_lowercase(std::string str) {
    std::stringstream out;
    for (auto c : str) {
        out << (char)std::tolower(c);
    }
    return out.str();
}

std::string char_format(const std::string& to_format, const uchar* data) {
    std::stringstream out;
    std::stringstream format;
    bool in_code = false;
    bool mods = true;
    char mod_mask = 0;
    char skip = 0;
    ulong start = 0, end = 0;
    for (ulong i = 0; i < to_format.length(); i++) {
        if (skip > 0) {
            skip--;
        } else if (!in_code && to_format[i] != '{') { // Assuming it's not a format code, just push it to output
            out << to_format[i];
        } else if (!in_code) { // If it's an { then we start processing a format code
            in_code = true;
        } else {
            if (to_format[i] == '}') { // If we find a } then we stop processing a format code, and dump the format result
                in_code = false, mods = true;
                out << format.str();
                format.str("");
                format.clear();
                start = 0, end = 0;
                mod_mask = 0;
                continue;
            } else if (mods && ((to_format[i] >= 'A' && to_format[i] <= 'Z') || (to_format[i] >= 'a' && to_format[i] <= 'z'))) { // If we're in the mod_code section, read in codes.
                if (to_format[i] == 's') {
                    mod_mask |= 0b10;
                } else if (to_format[i] == 'a') {
                    mod_mask |= 0b1000;
                } else if (to_format[i] == 'x') {
                    mod_mask |= 0b1;
                } else if (to_format[i] == 'X') {
                    mod_mask |= 0b101;
                } else {
                    throw std::runtime_error("Bad Mod Code");
                }
            } else if (mods && (to_format[i] == '|' || mod_mask == 0)) { // If there aren't any mods or we hit section end, move on to next section.
                mods = false;
            }
            if (!mods && to_format[i] != '|') {
                mods = false;
                for (ulong j = i; to_format[j] != '}' && to_format[j] != ','; j++) {
                    format << to_format[j];
                    skip++;
                }
                if (start == 0) {
                    format >> start;
                    format.str("");
                    format.clear();
                } else {
                    format >> end;
                    format.str("");
                    format.clear();
                }
                if (start != 0 && end != 0) {
                    ulong uresult = get_range(data, start, end);
                    slong result = get_signed_range(data, start, end);
                    if (mod_mask & 0b100) {
                        format << std::uppercase;
                    }
                    if (mod_mask & 0b10) {
                        if (mod_mask & 0b1) {
                            format << ltoh(result);
                        } else {
                            format << result;
                        }
                    } else if (mod_mask & 0b1000) {
                        if (mod_mask & 0b1) {
                            format << ltoh(std::abs(result));
                        } else {
                            format << std::abs(result);
                        }
                    } else {
                        if (mod_mask & 0b1) {
                            format << ltoh(uresult);
                        } else {
                            format << uresult;
                        }
                    }
                    format << std::nouppercase;
                    skip--;
                }
            }
        }
    }
    return out.str();
}

}
