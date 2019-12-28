
#include "reflection/variant.h"

namespace reflect {

Variant Variant::from_type(Type *type) {
    Variant out = Variant();
    out.type = type;
    return out;
}

Variant Variant::from_pair(Type *type, void *data) {
    Variant out = Variant();
    out.type = type;
    out.data = data;
    return out;
}

Type* Variant::get_type() {
    return type;
}

void* Variant::get_value_unsafe() {
    return data;
}

}
