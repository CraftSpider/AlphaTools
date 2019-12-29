
namespace reflect {

template<typename T>
Variant Variant::from_ptr(T* obj) {
    Variant out = Variant();
    out.type = Type::from<T>();
    out.data = reinterpret_cast<void*>(obj);
    return out;
}

template<typename T>
Variant Variant::from_ref(T& obj) {
    Variant out = Variant();
    out.type = Type::from<T>();
    out.data = reinterpret_cast<void*>(&obj);
    return out;
}

template<typename T>
Variant Variant::from_instance(T obj) {
    Variant out = Variant();
    out.type = Type::from<T>();
    out.data = new T(obj);
    return out;
}

template<typename T>
typename std::remove_reference_t<T>* Variant::get_value_ptr() {
    if (Type::from<T>() != type) {
        throw invalid_type("Attempt to retrieve value as wrong type: Expected '" + type->get_name() + "', got '" + Type::from<T>()->get_name() + "'");
    }
    
    return reinterpret_cast<typename std::remove_reference_t<T>*>(data);
}

template<typename T>
typename std::remove_reference_t<T>& Variant::get_value_ref() {
    if (Type::from<T>() != type) {
        throw invalid_type("Attempt to retrieve value as wrong type: Expected '" + type->get_name() + "', got '" + Type::from<T>()->get_name() + "'");
    }
    
    return *reinterpret_cast<typename std::remove_reference_t<T>*>(data);
}

template<typename T>
T Variant::get_value() {
    if (Type::from<T>() != type) {
        throw invalid_type("Attempt to retrieve value as wrong type: Expected '" + type->get_name() + "', got '" + Type::from<T>()->get_name() + "'");
    }
    
    return *reinterpret_cast<typename std::remove_reference_t<T>*>(data);
}

}
