
#include "reflection/constructor.h"

namespace reflect {

Variant Constructor::construct() {
    if (num_args != 0) {
        throw invalid_size("Constructor is not zero-arg");
    }
    
    std::vector<Variant> temp;
    return Variant::from_pair_owned(
        type,
        ptr(temp)
    );
}

Variant Constructor::construct(std::vector<Variant> args) {
    if (args.size() != num_args) {
        throw invalid_size("Invalid number of arguments to constructor");
    }
    for (size_t i = 0; i < num_args; ++i) {
        if (args[i].get_type() != arg_types[i]) {
            throw invalid_type("Invalid argument type " + args[i].get_type()->get_name());
        }
    }
    
    return Variant::from_pair_owned(
        type,
        ptr(args)
    );
}

void* Constructor::construct_unsafe(std::vector<Variant> args) {
    if (args.size() != num_args) {
        throw invalid_size("Invalid number of arguments to constructor");
    }
    for (size_t i = 0; i < num_args; ++i) {
        if (args[i].get_type() != arg_types[i]) {
            throw invalid_type("Invalid argument type " + args[i].get_type()->get_name());
        }
    }
    
    return ptr(args);
}

Type* Constructor::get_type() {
    return type;
}

const std::vector<Type*>& Constructor::get_arg_types() {
    return arg_types;
}

size_t Constructor::get_num_args() {
    return num_args;
}

}
