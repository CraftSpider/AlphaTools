
namespace reflect {

template<typename T, typename... Args>
std::vector<Type*> ConstructorMeta<T, Args...>::get_arg_types() {
    return Type::from_list<Args...>();
}

template<typename T, typename... Args>
T* ConstructorMeta<T, Args...>::construct(std::vector<Variant> args) {
    size_t i = 0;
    return new T((*args[i++].get_value_ptr<Args>())...);
}

template<typename T, typename... Args>
ConstructFuncRef ConstructorMeta<T, Args...>::get_construct_func() {
    return (ConstructFuncRef)&construct;
}

template<typename T, typename... Args>
Constructor::Constructor(reflect::Type* t, reflect::ConstructorMeta<T, Args...> meta) {
    (void)meta;
    type = t;
    arg_types = ConstructorMeta<T, Args...>::get_arg_types();
    ptr = ConstructorMeta<T, Args...>::get_construct_func();
    num_args = ConstructorMeta<T, Args...>::num_args;
}

template<typename T, typename... Args>
Constructor& Constructor::from() {
    static Constructor constructor = Constructor(
        Type::from<T>(),
        ConstructorMeta<T, Args...>()
    );
    
    return constructor;
}

}
