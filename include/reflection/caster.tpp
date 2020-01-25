
namespace reflect {

template<typename T>
Variant ShifterMeta<T>::add_pointer(Variant& obj) {
    return Variant::from_pair_owned(
        obj.get_type()->add_pointer(),
        obj.get_value_ptr<T>()
    );
}

template<typename T>
template<typename K>
std::enable_if_t<std::is_pointer_v<K>, Variant> ShifterMeta<T>::remove_pointer(Variant& obj) {
    return Variant::from_pair(
        obj.get_type()->remove_pointer(),
        obj.get_value_ref<K>()
    );
}

template<typename T>
template<typename K>
std::enable_if_t<!std::is_pointer_v<K>, Variant> ShifterMeta<T>::remove_pointer(Variant&) {
    throw invalid_cast("Type '" + Type::from<K>()->get_name() + "' is not a pointer type");
}

template<typename T>
CastFuncRef ShifterMeta<T>::get_add_pointer_func() {
    return &add_pointer;
}

template<typename T>
CastFuncRef ShifterMeta<T>::get_remove_pointer_func() {
    return &remove_pointer<T>;
}

template<typename T, typename K>
template<typename T1, typename K1>
std::enable_if_t<__CastSupport<T1, K1>::support_dynamic, Variant> CasterMeta<T, K>::cast_dynamic(Variant& obj) {
    return Variant::from_return(
        dynamic_cast<K>(obj.get_value_ref<T>())
    );
}

template<typename T, typename K>
template<typename T1, typename K1>
std::enable_if_t<!__CastSupport<T1, K1>::support_dynamic, Variant> CasterMeta<T, K>::cast_dynamic(Variant&) {
    return Variant::from_type(Type::from<void>());
}

template<typename T, typename K>
template<typename T1, typename K1>
std::enable_if_t<__CastSupport<T1, K1>::support_reinterpret, Variant> CasterMeta<T, K>::cast_reinterpret(Variant& obj) {
    return Variant::from_return(
        reinterpret_cast<K>(obj.get_value_ref<T>())
    );
}

template<typename T, typename K>
template<typename T1, typename K1>
std::enable_if_t<!__CastSupport<T1, K1>::support_reinterpret, Variant> CasterMeta<T, K>::cast_reinterpret(Variant&) {
    return Variant::from_type(Type::from<void>());
}

template<typename T, typename K>
template<typename T1, typename K1>
std::enable_if_t<__CastSupport<T1, K1>::support_static, Variant> CasterMeta<T, K>::cast_static(Variant& obj) {
    return Variant::from_return(
        static_cast<K>(obj.get_value_ref<T>())
    );
}

template<typename T, typename K>
template<typename T1, typename K1>
std::enable_if_t<!__CastSupport<T1, K1>::support_static, Variant> CasterMeta<T, K>::cast_static(Variant&) {
    return Variant::from_type(Type::from<void>());
}

template<typename T, typename K>
template<typename T1, typename K1>
std::enable_if_t<__CastSupport<T1, K1>::support_const, Variant> CasterMeta<T, K>::cast_const(Variant& obj) {
    return Variant::from_return(
        static_cast<K>(obj.get_value_ref<T>())
    );
}

template<typename T, typename K>
template<typename T1, typename K1>
std::enable_if_t<!__CastSupport<T1, K1>::support_const, Variant> CasterMeta<T, K>::cast_const(Variant&) {
    return Variant::from_type(Type::from<void>());
}

template<typename T, typename K>
template<typename T1, typename K1>
std::enable_if_t<__CastSupport<T1, K1>::support_c, Variant> CasterMeta<T, K>::cast_c(Variant& obj) {
    return Variant::from_return(
        (K)obj.get_value_ref<T>()
    );
}

template<typename T, typename K>
template<typename T1, typename K1>
std::enable_if_t<!__CastSupport<T1, K1>::support_c, Variant> CasterMeta<T, K>::cast_c(Variant&) {
    return Variant::from_type(Type::from<void>());
}

template<typename T, typename K>
CastFuncRef CasterMeta<T, K>::get_cast_reinterpret_func() {
    return &cast_reinterpret<T, K>;
}

template<typename T, typename K>
CastFuncRef CasterMeta<T, K>::get_cast_static_func() {
    return &cast_static<T, K>;
}

template<typename T, typename K>
CastFuncRef CasterMeta<T, K>::get_cast_const_func() {
    return &cast_const<T, K>;
}

template<typename T, typename K>
CastFuncRef CasterMeta<T, K>::get_cast_dynamic_func() {
    return &cast_dynamic<T, K>;
}

template<typename T, typename K>
CastFuncRef CasterMeta<T, K>::get_cast_c_func() {
    return &cast_c<T, K>;
}

template<typename T, typename K>
TypeCaster::TypeCaster(CasterMeta<T, K>) {
    from_type = Type::from<T>();
    to_type = Type::from<K>();
    
    reinterpret_ptr = CasterMeta<T, K>::get_cast_reinterpret_func();
    static_ptr = CasterMeta<T, K>::get_cast_static_func();
    const_ptr = CasterMeta<T, K>::get_cast_const_func();
    dynamic_ptr = CasterMeta<T, K>::get_cast_dynamic_func();
    c_ptr = CasterMeta<T, K>::get_cast_c_func();
}

template<typename T, typename K>
TypeCaster& TypeCaster::from() {
    static TypeCaster* type_caster = new TypeCaster(
        CasterMeta<T, K>()
    );
    
    return *type_caster;
}

template<typename T>
Caster::Caster(ShifterMeta<T>) {
    type = Type::from<T>();
    
    add_ptr = ShifterMeta<T>::get_add_pointer_func();
    remove_ptr = ShifterMeta<T>::get_remove_pointer_func();
}

template<typename T>
Caster& Caster::from() {
    static Caster* caster = new Caster(
        ShifterMeta<T>()
    );
    
    return *caster;
}

template<typename T, typename K>
void Caster::__add_cast() {
    if (registered_casts.count(Type::from<T>()) > 0) {
        throw already_reflected(
            "TypeCaster from type '" + Type::from<T>()->get_name() +
            "' to type '" + Type::from<K>()->get_name() + "' has already been set"
        );
    }
    registered_casts[Type::from<T>()] = &TypeCaster::from<T, K>();
}

}
