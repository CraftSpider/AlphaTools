
#include <typeinfo>
#include "reflection/errors.h"

namespace reflect {

template<typename T>
std::string MetaType<T>::raw_name() {
    return "[UNKNOWN TYPE]";
}

template<typename T>
std::string MetaType<T>::get_name() {
    return raw_name();
}

template<typename T>
Type::Type(MetaType<T>) {
    name = MetaType<T>::get_name();
    final = std::is_final<T>::value;
}

template<typename T>
Type* Type::from() {
    std::map<std::string, Type*>& types = __type_map();
    std::string name = MetaType<T>::get_name();
    
    if (name == "[UNKNOWN TYPE]") {
        throw not_reflected("Attempt to get unregistered type '" + std::string(typeid(T).name()) + "'. Make sure to DECLARE_TYPE(typename).");
    }
    
    if (types.count(name) == 0) {
        types[name] = new Type(MetaType<T>());
    }
    
    return types[name];
}

template<typename T>
Type* Type::from_instance(T*) {
    std::map<std::string, Type*>& types = __type_map();
    std::string name = MetaType<T>::get_name();
    
    if (name == "[UNKNOWN TYPE]") {
        throw not_reflected("Attempt to get unregistered type '" + std::string(typeid(T).name()) + "'. Make sure to DECLARE_TYPE(typename).");
    }
    
    if (types.count(name) == 0) {
        types[name] = new Type(MetaType<T>());
    }
    
    return types[name];
}

template<typename... Args>
std::vector<Type*> Type::from_list() {
    return {from<Args>()...};
}

}
