
namespace reflect {

template<typename T, typename Ret>
Variant MemberPropertyMeta<T, Ret>::get(Ret T::** ptr, Variant& instance) {
    return Variant::from_ref(instance.get_value_ref<T>().*(*ptr));
}

template<typename T, typename Ret>
void MemberPropertyMeta<T, Ret>::set(Ret T::** ptr, Variant& instance, Variant& data) {
    instance.get_value_ref<T>().*(*ptr) = data.get_value_ref<Ret>();
}

template<typename T, typename Ret>
MemberPropertyGetFuncRef MemberPropertyMeta<T, Ret>::get_get_func() {
    return (MemberPropertyGetFuncRef)&get;
}

template<typename T, typename Ret>
MemberPropertySetFuncRef MemberPropertyMeta<T, Ret>::get_set_func() {
    return (MemberPropertySetFuncRef)&set;
}

template<typename T, typename Ret>
MemberProperty::MemberProperty(Ret T::* ptr, std::string name) {
    type = Type::from<T>();
    property_type = Type::from<Ret>();
    this->name = std::move(name);
    
    this->ptr = new Ret T::*(ptr);
    get_ptr = MemberPropertyMeta<T, Ret>::get_get_func();
    set_ptr = MemberPropertyMeta<T, Ret>::get_set_func();
}

template<typename T, typename Ret>
MemberProperty& MemberProperty::from(Ret T::* ptr, std::string name) {
    static std::map<std::string, MemberProperty*> member_properties = std::map<std::string, MemberProperty*>();
    
    if (member_properties.count(name) == 0) {
        member_properties[name] = new MemberProperty(ptr, name);
    }
    
    return *member_properties[name];
}

}
