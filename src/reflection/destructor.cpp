
#include "reflection/destructor.h"

namespace reflect {

void Destructor::destruct(Variant instance) {
    if (instance.get_type() != type) {
        throw invalid_type("Attempt to destruct instance with invalid type");
    }
    
    if (instance.get_owned()) {
        throw variant_error("Variant owns its pointer, destructing it will cause a double-free");
    }
    
    ptr(instance.get_value_unsafe());
}

void Destructor::unsafe_destruct(void* instance) {
    ptr(instance);
}

Type* Destructor::get_type() {
    return type;
}

}
