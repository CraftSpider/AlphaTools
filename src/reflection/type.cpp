
#include "reflection/type.h"

namespace reflect {

std::map<std::string, Type*>& Type::__type_map() {
    static std::map<std::string, Type*> types = std::map<std::string, Type*>();
    return types;
}

Type* Type::from_name(const std::string &name) {
    static std::map<std::string, Type*> types = __type_map();
    
    if (types.count(name) == 0) {
        return nullptr;
    }
    return types[name];
}

void Type::__add_constructor(reflect::Constructor* constructor) {
    this->constructors.emplace_back(constructor);
}

const std::string& Type::get_name() {
    return name;
}

const std::vector<Constructor *> & Type::get_constructors() {
    return constructors;
}

const std::vector<MemberProperty *> & Type::get_properties() {
    return member_properties;
}

const std::vector<MemberFunction *> & Type::get_functions() {
    return member_functions;
}

Destructor * Type::get_destructor() {
    return destructor;
}

}
