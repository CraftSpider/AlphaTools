
#include "reflection/static_func.h"

namespace reflect {

Variant StaticFunction::invoke() {
    if (num_args != 0) {
        throw invalid_size("Invalid number of arguments to function");
    }
    
    std::vector<Variant> temp;
    return invoke_ptr(ptr, temp);
}

Variant StaticFunction::invoke(std::vector<Variant> args) {
    if (args.size() != num_args) {
        throw invalid_size("Invalid number of arguments to function");
    }
    for (size_t i = 0; i < num_args; ++i) {
        if (args[i].get_type() != arg_types[i]) {
            throw invalid_type("Invalid argument type " + args[i].get_type()->get_name());
        }
    }
    
    return invoke_ptr(ptr, args);
}

Type* StaticFunction::get_type() {
    return type;
}

Type* StaticFunction::get_return_type() {
    return return_type;
}

const std::vector<Type*>& StaticFunction::get_arg_types() {
    return arg_types;
}

size_t StaticFunction::get_num_args() {
    return num_args;
}

std::string StaticFunction::get_name() {
    return name;
}

}
