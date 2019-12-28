
#include "reflection/member_prop.h"

namespace reflect {

Variant MemberProperty::get(Variant instance) {
    if (instance.get_type() != type) {
        throw invalid_type("Attempt to get property from instance of invalid type");
    }
    
    return get_ptr(ptr, instance);
}

void MemberProperty::set(Variant instance, Variant value) {
    if (instance.get_type() != type) {
        throw invalid_type("Attempt to set property on instance of invalid type");
    }
    if (value.get_type() != property_type) {
        throw invalid_type("Attempt to set property to an invalid value type");
    }
    
    set_ptr(ptr, instance, value);
}

Type* MemberProperty::get_type() {
    return type;
}

Type* MemberProperty::get_property_type() {
    return property_type;
}

std::string MemberProperty::get_name() {
    return name;
}

}
