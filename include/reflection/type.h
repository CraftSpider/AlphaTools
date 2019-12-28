#pragma once

#include <vector>
#include <map>

namespace reflect {

// Forward refs
class Constructor;
class MemberProperty;
class MemberFunction;
class Destructor;


template<typename T>
class MetaType {
    
    friend class Type;
    
    static std::string get_name();
    
};


class Type {
    
    std::string name;
    
    std::vector<Constructor*> constructors;
    std::vector<MemberProperty*> member_properties;
    std::vector<MemberFunction*> member_functions;
    Destructor* destructor = nullptr;
    
    template<typename T>
    explicit Type(MetaType<T> meta);
    
    static std::map<std::string, Type*>& __type_map();

public:
    
    template<typename T>
    static Type* from();
    
    template<typename T>
    static Type* from_instance(T*);
    
    static Type* from_name(const std::string& name);
    
    template<typename... Args>
    static std::vector<Type*> from_list();
    
    void __add_constructor(Constructor* constructor);
    
    const std::string& get_name();
    
    const std::vector<Constructor*>& get_constructors();
    
    const std::vector<MemberProperty*>& get_properties();
    
    const std::vector<MemberFunction*>& get_functions();
    
    Destructor* get_destructor();
    
};

}

#include "type.tpp"
