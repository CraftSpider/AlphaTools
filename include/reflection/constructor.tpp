
#include "utils/sfinae.h"

namespace reflect {

/**
 * \internal
 *
 * Special function for actually doing construction, passed a template range
 *
 * \tparam T Type to construct
 * \tparam Args Arguments to function
 * \tparam I Indicies of args
 * \param args List of arguments to constructor
 * \return New instance of type
 */
template<typename T, typename... Args, size_t... I>
T* __construct_impl(std::vector<Variant>& args, util::TemplateRange<I...>) {
    return new T(args[I].get_value_ref<Args>()...);
}

template<typename T, typename... Args>
T* ConstructorMeta<T, Args...>::construct(std::vector<Variant>& args) {
    return __construct_impl<T, Args...>(args, util::VariadicRange<Args...>());
}

template<typename T, typename... Args>
ConstructFuncRef ConstructorMeta<T, Args...>::get_construct_func() {
    return (ConstructFuncRef)&construct;
}

template<typename T, typename... Args>
Constructor::Constructor(ConstructorMeta<T, Args...> meta) {
    (void)meta;
    type = Type::from<T>();
    arg_types = Type::from_list<Args...>();
    ptr = ConstructorMeta<T, Args...>::get_construct_func();
    num_args = sizeof...(Args);
}

template<typename T, typename... Args>
Constructor& Constructor::from() {
    static Constructor constructor = Constructor(ConstructorMeta<T, Args...>());
    
    return constructor;
}

}
