
namespace reflect {

template<typename Ret>
Variant StaticPropertyMeta<Ret>::get(Ret* ptr) {
    return Variant::from_ptr(ptr);
}

template<typename Ret>
void StaticPropertyMeta<Ret>::set(Ret* ptr, Variant& data) {
    *ptr = data.get_value_ref<Ret>();
}

template<typename Ret>
StaticPropertyGetFuncRef StaticPropertyMeta<Ret>::get_get_func() {
    return (StaticPropertyGetFuncRef)&get;
}

template<typename Ret>
StaticPropertySetFuncRef StaticPropertyMeta<Ret>::get_set_func() {
    return (StaticPropertySetFuncRef)&set;
}

template<typename Ret>
StaticProperty::StaticProperty(Type* type, Ret* ptr, std::string name) {
    this->type = type;
    this->property_type = Type::from<Ret>();
    this->name = std::move(name);
    
    this->ptr = ptr;
    this->get_ptr = StaticPropertyMeta<Ret>::get_get_func();
    this->set_ptr = StaticPropertyMeta<Ret>::get_set_func();
}

template<typename T, typename Ret>
StaticProperty& StaticProperty::from(Ret* ptr, std::string name) {
    static std::map<std::string, StaticProperty*> static_properties = std::map<std::string, StaticProperty*>();
    
    if (static_properties.count(name) == 0) {
        static_properties[name] = new StaticProperty(Type::from<T>(), ptr, name);
    }
    
    return *static_properties[name];
}

}
