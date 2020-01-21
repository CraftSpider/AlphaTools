
#include "reflection/variant.h"
#include "reflection/constructor.h"
#include "reflection/destructor.h"

namespace reflect {

std::map<void*, size_t> Variant::refcount = std::map<void*, size_t>();

void Variant::increment_refcount(void* data) {
    if (refcount.count(data) == 0) {
        refcount[data] = 1;
    } else {
        refcount[data]++;
    }
}

void Variant::decrement_refcount(void* data) {
    refcount[data]--;
    if (refcount[data] == 0) {
        refcount.erase(data);
    }
}

size_t Variant::get_refcount(void* data) {
    if (refcount.count(data) == 0) {
        return 0;
    }
    return refcount[data];
}

void Variant::destruct_data() {
    if (owned) {
        decrement_refcount(data);
        if (get_refcount(data) == 0) {
            // Actually safe, because we know the type of data
            type->get_destructor()->unsafe_destruct(data);
        }
    }
}

Variant::Variant(const reflect::Variant& other) {
    this->type = other.type;
    this->data = other.data;
    this->owned = other.owned;
    
    if (owned) {
        increment_refcount(data);
    }
}

Variant::Variant(reflect::Variant&& other) noexcept {
    this->type = other.type;
    this->data = other.data;
    this->owned = other.owned;
    
    other.type = nullptr;
    other.data = nullptr;
    other.owned = false;
}

Variant::~Variant() {
    destruct_data();
}

Variant& Variant::operator=(const Variant &other) {
    // If we're self-assigning, we don't need to do anything
    if (&other == this) {
        return *this;
    }
    
    destruct_data();
    
    this->type = other.type;
    this->data = other.data;
    this->owned = other.owned;
    
    if (owned) {
        increment_refcount(data);
    }
    
    return *this;
}

Variant& Variant::operator=(Variant &&other) noexcept {
    destruct_data();
    
    this->type = other.type;
    this->data = other.data;
    this->owned = other.owned;
    
    other.type = nullptr;
    other.data = nullptr;
    other.owned = false;
    
    return *this;
}

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

Variant Variant::from_pair_owned(Type* type, void* data) {
    Variant out = Variant();
    out.type = type;
    out.data = data;
    out.owned = true;
    
    increment_refcount(out.data);
    return out;
}

Type* Variant::get_type() const {
    return type;
}

void* Variant::get_value_unsafe() {
    return data;
}

void* Variant::take_value_unsafe() {
    if (owned) {
        owned = false;
        if (refcount[data] != 1) {
            throw variant_error("Cannot take ownership of a pointer with more than one Variant referencing it");
        }
        refcount.erase(data);
    }
    return data;
}

bool Variant::get_owned() const {
    return owned;
}

}
