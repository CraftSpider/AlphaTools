
#include "reflection/caster.h"

namespace reflect {

Variant TypeCaster::cast(Variant &variant, CastType type) {
    switch (type) {
        case CastType::DYNAMIC:
            if (dynamic_ptr == nullptr) break;
            return dynamic_ptr(variant);
        case CastType::CONST:
            if (const_ptr == nullptr) break;
            return const_ptr(variant);
        case CastType::STATIC:
            if (static_ptr == nullptr) break;
            return static_ptr(variant);
        case CastType::REINTERPRET:
            if (reinterpret_ptr == nullptr) break;
            return reinterpret_ptr(variant);
        case CastType::C:
            if (c_ptr == nullptr) break;
            return c_ptr(variant);
    }
    
    throw invalid_cast("Cast type X from type A to type B is not supported"); // TODO: X, A, and B are names
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
