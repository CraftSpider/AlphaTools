
#include "reflection/member_func.h"

namespace reflect {

Variant MemberFunction::invoke(Variant instance) {
    if (instance.get_type() != type) {
        throw invalid_type("Attempt to invoke function on instance of invalid type");
    }
    if (num_args != 0) {
        throw invalid_size("Function is not zero-arg");
    }
    
    std::vector<Variant> temp;
    return invoke_ptr(ptr, instance, temp);
}

Variant MemberFunction::invoke(reflect::Variant instance, std::vector<Variant> args) {
    if (instance.get_type() != type) {
        throw invalid_type("Attempt to invoke function on instance of invalid type");
    }
    if (args.size() != num_args) {
        throw invalid_size("Invalid number of arguments to function");
    }
    for (size_t i = 0; i < num_args; ++i) {
        if (args[i].get_type() != arg_types[i]) {
            throw invalid_type("Invalid argument type " + args[i].get_type()->get_name());
        }
    }
    
    return invoke_ptr(ptr, instance, args);
}

Type* MemberFunction::get_type() {
    return type;
}

Type* MemberFunction::get_return_type() {
    return return_type;
}

const std::vector<Type*>& MemberFunction::get_arg_types() {
    return arg_types;
}

size_t MemberFunction::get_num_args() {
    return num_args;
}

std::string MemberFunction::get_name() {
    return name;
}

}
