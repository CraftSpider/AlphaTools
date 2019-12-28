
namespace reflect {

template<typename T>
Variant Variant::from_instance(T* obj) {
    Variant out = Variant();
    out.type = Type::from<T>();
    out.data = reinterpret_cast<void*>(obj);
    return out;
}

template<typename T>
Variant Variant::from_instance(T& obj) {
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
T* Variant::get_value_ptr() {
    return reinterpret_cast<T*>(data);
}

template<typename T>
T& Variant::get_value_ref() {
    return *reinterpret_cast<T*>(data);
}

template<typename T>
T Variant::get_value() {
    return *reinterpret_cast<T*>(data);
}

}
