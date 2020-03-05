
#include <algorithm>
#include "reflection/type.h"
#include "reflection/constructor.h"
#include "reflection/member_prop.h"
#include "reflection/member_func.h"
#include "reflection/static_prop.h"
#include "reflection/static_func.h"

namespace reflect {

std::map<std::string, Type*>& Type::__type_map() {
    static std::map<std::string, Type*> types = std::map<std::string, Type*>();
    return types;
}

Type* Type::from_name(const std::string& name) {
    static std::map<std::string, Type*> types = __type_map();
    
    if (types.count(name) == 0) {
        throw not_reflected("Attempt to get unregistered type '" + name + "'. Make sure to DECLARE_TYPE(typename).");
    }
    
    return types[name];
}

void Type::__add_parent_class(Type* parent) {
    if (std::find(parents.begin(), parents.end(), parent) != parents.end()) {
        throw already_reflected("Parent class for type '" + get_name() + "' has already been added");
    }
    this->parents.emplace_back(parent);
}

void Type::__add_child_class(Type* child) {
    if (std::find(children.begin(), children.end(), child) != children.end()) {
        throw already_reflected("Child class for type '" + get_name() + "' has already been added");
    }
    this->children.emplace_back(child);
}

void Type::__add_constructor(Constructor* constructor) {
    if (std::find(constructors.begin(), constructors.end(), constructor) != constructors.end()) {
        throw already_reflected("Constructor for type '" + get_name() + "' has already been added");
    }
    this->constructors.emplace_back(constructor);
}

void Type::__add_member_property(MemberProperty* property) {
    if (std::find(member_properties.begin(), member_properties.end(), property) != member_properties.end()) {
        throw already_reflected("Member Property for type '" + get_name() + "' has already been added");
    }
    this->member_properties.emplace_back(property);
}

void Type::__add_member_function(MemberFunction* function) {
    if (std::find(member_functions.begin(), member_functions.end(), function) != member_functions.end()) {
        throw already_reflected("Member function for type '" + get_name() + "' has already been added");
    }
    this->member_functions.emplace_back(function);
}

void Type::__add_static_property(StaticProperty* property) {
    if (std::find(static_properties.begin(), static_properties.end(), property) != static_properties.end()) {
        throw already_reflected("Member function for type '" + get_name() + "' has already been added");
    }
    this->static_properties.emplace_back(property);
}

void Type::__add_static_function(StaticFunction* function) {
    if (std::find(static_functions.begin(), static_functions.end(), function) != static_functions.end()) {
        throw already_reflected("Member function for type '" + get_name() + "' has already been added");
    }
    this->static_functions.emplace_back(function);
}

void Type::__set_destructor(Destructor* destructor) {
    if (this->destructor != nullptr) {
        throw already_reflected("Destructor for type '" + get_name() + "' has already been set");
    }
    this->destructor = destructor;
}

void Type::__set_caster(Caster* caster) {
    if (this->caster != nullptr) {
        throw already_reflected("Caster for type '" + get_name() + "' has already been set");
    }
    this->caster = caster;
}

const std::string& Type::get_name() {
    return name;
}

bool Type::is_final() {
    return final;
}

Type* Type::add_pointer() {
    return Type::from_name(name + "*");
}

Type* Type::remove_pointer() {
    if (name.find('*') != std::string::npos) {
        std::string new_name = name;
        return Type::from_name(
            new_name.erase(name.find_last_of('*'), 1)
        );
    }
    throw invalid_type("Cannot remove a pointer from a non-pointer type");
}

const std::vector<Type*>& Type::get_parents() {
    return parents;
}

const std::vector<Type*>& Type::get_children() {
    return children;
}

const std::vector<Constructor*>& Type::get_constructors() {
    return constructors;
}

Constructor* Type::get_constructor(std::vector<Type*> types) {
    for (auto c : constructors) {
        if (types.size() != c->get_arg_types().size()) {
            continue;
        }
        for (size_t i = 0; i < types.size(); ++i) {
            if (types[i] != c->get_arg_types()[i]) {
                continue;
            }
        }
        return c;
    }
    return nullptr;
}

Constructor* Type::get_default_constructor() {
    for (auto c : constructors) {
        if (c->get_num_args() != 0) {
            continue;
        }
        return c;
    }
    return nullptr;
}

Constructor* Type::get_copy_constructor() {
    for (auto c : constructors) {
        if (c->get_num_args() != 1) {
            continue;
        }
        if (c->get_arg_types()[0] == Type::from_name("const " + name + "&")) {
            return c;
        }
    }
    return nullptr;
}

Constructor* Type::get_move_constructor() {
    for (auto c : constructors) {
        if (c->get_num_args() != 1) {
            continue;
        }
        if (c->get_arg_types()[0] == Type::from_name(name + "&&")) {
            return c;
        }
    }
    return nullptr;
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

std::vector<MemberFunction*> Type::get_functions(std::vector<Type*> types) {
    std::vector<MemberFunction*> out = std::vector<MemberFunction*>();
    
    for (auto f : member_functions) {
        if (f->get_arg_types() == types) {
            out.emplace_back(f);
        }
    }
    
    return out;
}

std::vector<MemberFunction*> Type::get_functions(std::string name) {
    std::vector<MemberFunction*> out = std::vector<MemberFunction*>();
    
    for (auto f : member_functions) {
        if (f->get_name() == name) {
            out.emplace_back(f);
        }
    }
    
    return out;
}

MemberFunction* Type::get_function(std::string name, std::vector<Type*> types) {
    for (auto f : member_functions) {
        if (f->get_name() == name && f->get_arg_types() == types) {
            return f;
        }
    }
    
    return nullptr;
}

const std::vector<StaticProperty*>& Type::get_static_properties() {
    return static_properties;
}

StaticProperty* Type::get_static_property(std::string name) {
    for (auto p : static_properties) {
        if (p->get_name() == name) {
            return p;
        }
    }
    return nullptr;
}

const std::vector<StaticFunction*>& Type::get_static_functions() {
    return static_functions;
}

StaticFunction* Type::get_static_function(std::string name) {
    for (auto f : static_functions) {
        if (f->get_name() == name) {
            return f;
        }
    }
    return nullptr;
}

Destructor* Type::get_destructor() {
    return destructor;
}

Caster* Type::get_caster() {
    return caster;
}

}
