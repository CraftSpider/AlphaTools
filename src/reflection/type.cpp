
#include <algorithm>
#include "reflection/type.h"
#include "reflection/member_prop.h"

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
    if (std::find(constructors.begin(), constructors.end(), constructor) != constructors.end()) {
        throw already_reflected("Constructor for type '" + name + "' has already been added");
    }
    this->constructors.emplace_back(constructor);
}

void Type::__add_member_property(MemberProperty *property) {
    if (std::find(member_properties.begin(), member_properties.end(), property) != member_properties.end()) {
        throw already_reflected("Member Property for type '" + name + "' has already been added");
    }
    this->member_properties.emplace_back(property);
}

void Type::__set_destructor(Destructor* destructor) {
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

MemberProperty* Type::get_property(std::string name) {
    for (auto p : member_properties) {
        if (p->get_name() == name) {
            return p;
        }
    }
    return nullptr;
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
