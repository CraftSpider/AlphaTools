
#include "reflection/caster.h"

namespace reflect {

Variant TypeCaster::cast(Variant &variant, CastType type) {
    
    CastFuncRef func = nullptr;
    switch (type) {
        case CastType::DYNAMIC:
            func = dynamic_ptr;
            break;
        case CastType::CONST:
            func = const_ptr;
            break;
        case CastType::STATIC:
            func = static_ptr;
            break;
        case CastType::REINTERPRET:
            func = reinterpret_ptr;
            break;
        case CastType::C:
            func = c_ptr;
            break;
    }
    
    Variant result = func(variant);
    
    if (result.get_type() == Type::from<void>()) {
        throw invalid_cast("Cast type X from type A to type B is not supported"); // TODO: X, A, and B are names
    }
    
    return result;
}

Variant Caster::add_pointer(Variant variant) {
    return add_ptr(variant);
}

Variant Caster::remove_pointer(Variant variant) {
    return remove_ptr(variant);
}

Variant Caster::cast(Type *type, Variant variant, CastType cast) {
    if (registered_casts.count(type) == 0) {
        throw invalid_type("Type '" + type->get_name() + "' is not registered for casting, use AT_DECLARE_TYPE_CAST()");
    }
    TypeCaster* type_caster = registered_casts[type];
    return type_caster->cast(variant, cast);
}

}
