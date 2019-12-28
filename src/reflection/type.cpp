
#include "reflection/type.h"
#include <iostream>

namespace reflect {

std::map<std::string, Type*>& Type::__type_map() {
    static std::map<std::string, Type*> types = std::map<std::string, Type*>();
    return types;
}

Type* Type::from_name(const std::string &name) {
    static std::map<std::string, Type*> types = __type_map();
    
    if (types.count(name) == 0) {
        throw invalid_type("Attempt to get unregistered type '" + name + "'. Make sure to DECLARE_TYPE(typename).");
    }
    
    return types[name];
}

void Type::__add_constructor(reflect::Constructor* constructor) {
    // TODO: Check to ensure it's not already in there, throw already_reflected
    this->constructors.emplace_back(constructor);
}

void Type::__set_destructor(Destructor* destructor) {
    if (name == "volatile char&&") {
        std::cout << name;
    }
    if (this->destructor != nullptr) {
        throw already_reflected("Destructor for type '" + name + "' has already been set");
    }
    this->destructor = destructor;
}

const std::string& Type::get_name() {
    return name;
}

const std::vector<Constructor*>& Type::get_constructors() {
    return constructors;
}

const std::vector<MemberProperty*>& Type::get_properties() {
    return member_properties;
}

const std::vector<MemberFunction*>& Type::get_functions() {
    return member_functions;
}

const std::vector<StaticProperty*>& Type::get_static_properties() {
    return static_properties;
}

const std::vector<StaticFunction*>& Type::get_static_functions() {
    return static_functions;
}

Destructor* Type::get_destructor() {
    return destructor;
}

}
