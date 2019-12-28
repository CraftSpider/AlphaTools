
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
