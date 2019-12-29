
#include "reflection/static_prop.h"

namespace reflect {

Variant StaticProperty::get() {
    return get_ptr(ptr);
}

void StaticProperty::set(Variant data) {
    return set_ptr(ptr, data);
}

Type* StaticProperty::get_type() {
    return type;
}

Type* StaticProperty::get_property_type() {
    return property_type;
}

std::string StaticProperty::get_name() {
    return name;
}

}
