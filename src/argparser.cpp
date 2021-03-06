#include "argparser.h"

#include <sstream>
#include "argparser.h"

ArgParser::ArgParser(int argc, const char** argv) {
    invokation = argv[0];
    
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        raw_args.push_back(arg);
        if (arg[0] == '-') {
            arg = arg.substr(1, arg.size());
            bool var = false;
            for (auto c : arg) {
                if (c == '=') {
                    var = true;
                    break;
                }
            }
            if (var) {
                if (arg[0] == '-') {
                    arg = arg.substr(1, arg.size());
                }
                std::stringstream name, option;
                var = false;
                for (auto c : arg) {
                    if (c == '=') {
                        var = true;
                    } else if (var) {
                        option << c;
                    } else {
                        name << c;
                    }
                }
                variables.emplace(name.str(), option.str());
            } else if (arg[0] == '-') {
                // read the whole thing for flags.
                arg = arg.substr(1, arg.size());
                flags.push_back(arg);
            } else {
                for (auto c : arg) {
                    flags.emplace_back(std::string(&c, 1));
                }
            }
        } else {
            arguments.push_back(arg);
        }
    }
}

ulong ArgParser::num_flags() {
    return flags.size();
}

ulong ArgParser::num_arguments() {
    return arguments.size();
}

ulong ArgParser::num_variables() {
    return variables.size();
}

bool ArgParser::has_flag(const std::string& flag) {
    for (const auto& f : flags) {
        if (f == flag) {
            return true;
        }
    }
    return false;
}

uint ArgParser::flag_count(const std::string& flag) {
    uint out = 0;
    for (const auto& f : flags) {
        if (f == flag) {
            out += 1;
        }
    }
    return out;
}

std::string ArgParser::get_argument(uint index) {
    return arguments.at(index);
}

bool ArgParser::has_variable(const std::string& var) {
    return (bool)variables.count(var);
}

std::string ArgParser::get_variable(const std::string& var) {
    return variables.at(var);
}