
namespace reflect {

template<typename T>
Variant ShifterMeta<T>::add_pointer(reflect::Variant& obj) {
    return Variant::from_pair_owned(
        obj.get_type()->add_pointer(),
        obj.get_value_ptr<T>()
    );
}

template<typename T>
template<typename K>
std::enable_if_t<std::is_pointer_v<K>, Variant> ShifterMeta<T>::remove_pointer(reflect::Variant& obj) {
    return Variant::from_pair_owned(
        obj.get_type()->remove_pointer(),
        obj.get_value_ref<K>()
    );
}

template<typename T>
template<typename K>
std::enable_if_t<!std::is_pointer_v<K>, Variant> ShifterMeta<T>::remove_pointer(reflect::Variant&) {
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
Variant CasterMeta<T, K>::cast_dynamic(reflect::Variant& obj) {
    return Variant::from_return(
        dynamic_cast<K>(obj.get_value_ref<T>())
    );
}

template<typename T, typename K>
Variant CasterMeta<T, K>::cast_reinterpret(reflect::Variant& obj) {
    return Variant::from_return(
        reinterpret_cast<K>(obj.get_value_ref<T>())
    );
}

template<typename T, typename K>
Variant CasterMeta<T, K>::cast_static(reflect::Variant& obj) {
    return Variant::from_return(
        static_cast<K>(obj.get_value_ref<T>())
    );
}

template<typename T, typename K>
Variant CasterMeta<T, K>::cast_const(reflect::Variant& obj) {
    return Variant::from_return(
        static_cast<K>(obj.get_value_ref<T>())
    );
}

template<typename T, typename K>
Variant CasterMeta<T, K>::cast_c(reflect::Variant& obj) {
    return Variant::from_return(
        (K)obj.get_value_ref<T>()
    );
}

template<typename T, typename K>
CastFuncRef CasterMeta<T, K>::get_cast_reinterpret_func() {
    return &cast_reinterpret;
}

template<typename T, typename K>
CastFuncRef CasterMeta<T, K>::get_cast_static_func() {
    return &cast_static;
}

template<typename T, typename K>
CastFuncRef CasterMeta<T, K>::get_cast_const_func() {
    return &cast_const;
}

template<typename T, typename K>
CastFuncRef CasterMeta<T, K>::get_cast_dynamic_func() {
    return &cast_dynamic;
}

template<typename T, typename K>
CastFuncRef CasterMeta<T, K>::get_cast_c_func() {
    return &cast_c;
}

template<typename T, typename K>
TypeCaster::TypeCaster(CasterMeta<T, K>) {
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
void Caster::__add_cast(CasterMeta<T, K> meta) {
    if (registered_casts.count(Type::from<T>()) > 0) {
        throw already_reflected(
            "TypeCaster from type '" + Type::from<T>()->get_name() +
            "' to type '" + Type::from<K>()->get_name() + "' has already been set"
        );
    }
    registered_casts[Type::from<T>()] = TypeCaster::from<T, K>();
}

}
