
namespace reflect {

template<typename T>
Variant Variant::from_ptr(T* obj) {
    Variant out = Variant();
    out.type = Type::from<T>();
    out.data = static_cast<void*>(obj);
    return out;
}

template<typename T>
Variant Variant::from_ref(T& obj) {
    Variant out = Variant();
    out.type = Type::from<typename std::remove_reference_t<T>>();
    out.data = static_cast<void*>(&obj);
    return out;
}

template<typename T>
Variant Variant::from_instance(T obj) {
    Variant out = Variant();
    out.type = Type::from<typename std::remove_reference_t<T>>();
    out.data = new typename std::remove_reference_t<T>(obj);
    out.owned = true;
    
    increment_refcount(out.data);
    return out;
}

template<typename T>
Variant Variant::from_return(T obj) {
    Variant out = Variant();
    out.type = Type::from<typename std::remove_reference_t<T>>();
    if constexpr(std::is_reference<T>::value) {
        out.data = const_cast<void*>(reinterpret_cast<const void*>(&obj));
    } else {
        out.data = new typename std::remove_reference_t<T>(std::move(obj));
        out.owned = true;
        
        increment_refcount(out.data);
    }
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
typename std::remove_reference_t<T>* Variant::take_value_ptr() {
    if (Type::from<T>() != type) {
        throw invalid_type("Attempt to retrieve value as wrong type: Expected '" + type->get_name() + "', got '" + Type::from<T>()->get_name() + "'");
    }
    
    if (owned) {
        owned = false;
        if (refcount[data] != 1) {
            throw variant_error("Cannot take ownership of a pointer with more than one Variant referencing it");
        }
        refcount.erase(data);
    }
    
    return reinterpret_cast<typename std::remove_reference_t<T>*>(data);
}

template<typename T>
typename std::remove_reference_t<T>& Variant::take_value_ref() {
    if (Type::from<T>() != type) {
        throw invalid_type("Attempt to retrieve value as wrong type: Expected '" + type->get_name() + "', got '" + Type::from<T>()->get_name() + "'");
    }
    
    if (owned) {
        owned = false;
        if (refcount[data] != 1) {
            throw variant_error("Cannot take ownership of a pointer with more than one Variant referencing it");
        }
        refcount.erase(data);
    }
    
    return *reinterpret_cast<typename std::remove_reference_t<T>*>(data);
}

template<typename T>
T Variant::get_value() const {
    if (Type::from<T>() != type) {
        throw invalid_type("Attempt to retrieve value as wrong type: Expected '" + type->get_name() + "', got '" + Type::from<T>()->get_name() + "'");
    }
    
    return *reinterpret_cast<typename std::remove_reference_t<T>*>(data);
}

}
