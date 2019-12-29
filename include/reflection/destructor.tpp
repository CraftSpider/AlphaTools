
namespace reflect {

template<typename T>
void DestructorMeta<T>::destruct(typename std::remove_reference_t<T>* instance) {
    delete instance;
}

template<typename T>
DestructFuncRef DestructorMeta<T>::get_destruct_func() {
    return (DestructFuncRef)&destruct;
}

template<typename T>
Destructor::Destructor(DestructorMeta<T> meta) {
    (void)meta;
    type = Type::from<T>();
    ptr = DestructorMeta<T>::get_destruct_func();
}

template<typename T>
Destructor& Destructor::from() {
    static Destructor destructor = Destructor(DestructorMeta<T>());
    return destructor;
}

}
