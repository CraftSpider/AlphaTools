
#include <sstream>

namespace util {

struct __Spec {
    std::string args;
    size_t pos;
};

template<typename T>
std::string spec_handler(std::string spec, T* arg) {
    return (*arg)->__format__(spec);
}

template<>
std::string spec_handler<int>(std::string spec, int* arg) {
    std::stringstream out;
    
    bool pref = false;
    if (spec.find('0') != std::string::npos)
        pref = true;
    if (spec.find('x') != std::string::npos)
        out << (pref ? "0x" : "") << std::hex;
    else if (spec.find('X') != std::string::npos)
        out << (pref ? "0x" : "") << std::hex << std::uppercase;
    else if (spec.find('o') != std::string::npos)
        out << (pref ? "0o" : "") << std::oct;
    
    out << *arg;
    return out.str();
}

template<>
std::string spec_handler<std::string>(std::string spec, std::string* arg) {
    std::stringstream out;
    std::string str = *arg;
    
    if (spec.find('u') != std::string::npos) {
        str = util::to_uppercase(str);
    } else if (spec.find('l') != std::string::npos) {
        str = util::to_lowercase(str);
    }
    
    if (spec.find('n') != std::string::npos)
        out << str.size();
    else
        out << str;
    
    return out.str();
}

template<>
std::string spec_handler<const char*>(std::string spec, const char** arg) {
    std::string temp = std::string(*arg);
    return spec_handler(spec, &temp);
}

template<>
std::string spec_handler<uchar*>(std::string spec, uchar** arg) {
    if (spec == "") {
        return "";
    }
    
    const uchar* bytes = *arg;
    std::stringstream out;
    
    size_t num_start = spec.find_first_of("1234567890");
    size_t comma_pos = spec.find(',');
    std::string mods = spec.substr(0, num_start);
    int start = std::stoi(spec.substr(num_start, comma_pos));
    int end = std::stoi(spec.substr(comma_pos + 1));
    
    uint mod_mask = 0;
    if (mods.find('s') != std::string::npos) {
        mod_mask |= 0b10u;
    }
    if (mods.find('x') != std::string::npos) {
        mod_mask |= 0b1u;
    }
    
    if (mods.find('a') != std::string::npos) {
        mod_mask |= 0b1010u;
    }
    if (mods.find('X') != std::string::npos) {
        mod_mask |= 0b101u;
    }
    
    if (mod_mask & 0b100u) {
        out << std::uppercase;
    }
    
    if (mod_mask & 0b10u) {
        slong result = util::get_signed_range(bytes, start, end);
        if (mod_mask & 0b1000u) {
            result = std::abs(result);
        }
        if (mod_mask & 0b1u) {
            out << util::ltoh(result);
        } else {
            out << result;
        }
    } else {
        ulong result = util::get_range(bytes, start, end);
        if (mod_mask & 0b1u) {
            out << util::ltoh(result);
        } else {
            out << result;
        }
    }
    
    return out.str();
}

template<typename... Args>
std::string format(std::string format, Args... args) {
    typedef std::string(*handler)(std::string, void*);
    
    size_t num_args = sizeof...(args);
    handler handlers[] = {(handler)(&spec_handler<Args>)...};
    void* arg_ptrs[] = {(void*)&args...};
    
    bool escaped = false, in_spec = false;
    size_t arg_count = 0;
    std::stringstream out, temp;
    std::vector<__Spec> specs;
    
    for (auto c : format) {
        if (escaped) {
            escaped = false;
            continue;
        } else if (in_spec) {
            if (c == '}') {
                std::string str = temp.str();
                size_t colon_pos = str.find(':');
                size_t arg_pos = 0;
                if (colon_pos != std::string::npos) {
                    arg_pos = std::stoi(str.substr(0, colon_pos));
                    str = str.substr(colon_pos+1);
                } else {
                    arg_pos = arg_count++;
                }
                specs.emplace_back(__Spec {str, arg_pos});
                temp = std::stringstream();
                in_spec = false;
            } else {
                temp << c;
            }
        } else if (c == '{') {
            in_spec = true;
        } else if (c == '\\') {
            escaped = true;
        } else {}
    }
    
    if (escaped) {
        throw format_error("Invalid escape at end of string");
    }
    if (in_spec) {
        throw format_error("Reached end of string in format spec");
    }
    
    for (const auto& s : specs) {
        if (s.pos > arg_count) {
            arg_count = s.pos;
        }

//        std::cout << s.pos << " " << s.args << "\n";
    }
    
    if (arg_count > num_args) {
        throw format_error("Too few arguments to format");
    }
    
    size_t spec_index = 0;
    escaped = false, in_spec = false;
    
    for (auto c : format) {
        if (escaped) {
            temp << c;
            escaped = false;
            continue;
        } else if (in_spec) {
            if (c == '}') {
                __Spec s = specs[spec_index++];
                temp << handlers[s.pos](s.args, arg_ptrs[s.pos]);
                in_spec = false;
            }
        } else if (c == '{') {
            in_spec = true;
        } else if (c == '\\') {
            escaped = true;
        } else {
            temp << c;
        }
    }
    
    return temp.str();
}

}
