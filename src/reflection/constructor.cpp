
#include "reflection/constructor.h"

namespace reflect {

Variant Constructor::construct(std::vector<Variant> args) {
    if (args.size() != num_args) {
        throw invalid_size("Invalid number of arguments to constructor");
    }
    for (size_t i = 0; i < num_args; ++i) {
        if (args[i].get_type() != arg_types[i]) {
            throw invalid_type("Invalid argument type [type]");
        }
    }
    
    return Variant::from_pair(
        type,
        ptr(std::move(args))
    );
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
