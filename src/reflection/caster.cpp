
#include "reflection/caster.h"
#include "reflection/declare_types.h"

namespace reflect {

namespace CastType {

std::string to_string(type t) {
    switch (t) {
        case DYNAMIC:
            return "DYNAMIC";
        case REINTERPRET:
            return "REINTERPRET";
        case STATIC:
            return "STATIC";
        case CONST:
            return "CONST";
        case C:
            return "C";
    }
    return "";
}

}

Variant TypeCaster::cast(Variant& variant, CastType::type type) {
    
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
        throw invalid_cast(
            "Cast type '" + CastType::to_string(type) +
            "' from type '" + from_type->get_name() +
            "' to type '" + to_type->get_name() +
            "' is not supported"
        );
    }
    
    return result;
}

Type* TypeCaster::get_from_type() {
    return from_type;
}

Type* TypeCaster::get_to_type() {
    return to_type;
}

Variant Caster::add_pointer(Variant variant) {
    return add_ptr(variant);
}

Variant Caster::remove_pointer(Variant variant) {
    return remove_ptr(variant);
}

Variant Caster::cast(Type* type, Variant variant, CastType::type cast) {
    if (registered_casts.count(type) == 0) {
        throw invalid_type("Type '" + type->get_name() + "' is not registered for casting, use AT_DECLARE_TYPE_CAST()");
    }
    TypeCaster* type_caster = registered_casts[type];
    return type_caster->cast(variant, cast);
}

Type* Caster::get_type() {
    return type;
}

}
