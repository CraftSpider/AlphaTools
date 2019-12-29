
#include "utils/sfinae.h"

namespace reflect {

template<typename Ret, typename... Args, size_t... I>
Variant __static_invoke_impl(Ret(*ptr)(Args...), std::vector<Variant>& args, util::TemplateRange<I...>) {
    if constexpr (std::is_same<void, Ret>::value) {
        ptr(args[I].get_value_ref<Args>()...);
        return Variant::from_type(Type::from<void>());
    } else {
        return Variant::from_return<Ret>(ptr(args[I].get_value_ref<Args>()...));
    }
}

template<typename Ret, typename... Args>
Variant StaticFunctionMeta<Ret, Args...>::invoke(Ret (*ptr)(Args...), std::vector<Variant>& args) {
    return __static_invoke_impl<Ret, Args...>(*ptr, args, util::VariadicRange<Args...>());
}

template<typename Ret, typename... Args>
StaticFunctionFuncRef StaticFunctionMeta<Ret, Args...>::get_invoke_func() {
    return (StaticFunctionFuncRef)&invoke;
}

template<typename Ret, typename... Args>
StaticFunction::StaticFunction(Type* type, Ret(*ptr)(Args...), std::string name) {
    this->type = type;
    this->return_type = Type::from<Ret>();
    this->arg_types = Type::from_list<Args...>();
    this->name = std::move(name);
    
    this->ptr = (void(*)())ptr;
    this->invoke_ptr = StaticFunctionMeta<Ret, Args...>::get_invoke_func();
    this->num_args = sizeof...(Args);
}

template<typename T, typename Ret, typename... Args>
StaticFunction& StaticFunction::from(Ret (*ptr)(Args...), std::string name) {
    static std::map<std::string, StaticFunction*> static_functions = std::map<std::string, StaticFunction*>();
    
    if (static_functions.count(name) == 0) {
        static_functions[name] = new StaticFunction(Type::from<T>(), ptr, name);
    }
    
    return *static_functions[name];
}

}
