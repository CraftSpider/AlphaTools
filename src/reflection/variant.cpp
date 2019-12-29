
#include "reflection/variant.h"
#include "reflection/constructor.h"
#include "reflection/destructor.h"

namespace reflect {

Variant::Variant(const reflect::Variant& other) {
    this->type = other.type;
    this->data = other.data;
}

Variant::Variant(reflect::Variant&& other) noexcept {
    this->type = other.type;
    this->data = other.data;
    other.data = nullptr;
}

Variant::~Variant() = default;

Variant Variant::from_type(Type* type) {
    Variant out = Variant();
    out.type = type;
    out.data = nullptr;
    return out;
}

Variant Variant::from_pair(Type* type, void* data) {
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
