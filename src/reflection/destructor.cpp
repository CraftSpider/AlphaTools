
#include "reflection/destructor.h"

namespace reflect {

void Destructor::destruct(Variant instance) {
    if (instance.get_type() != type) {
        throw invalid_type("Attempt to destruct instance with invalid type");
    }
    
    ptr(instance);
}

Type* Destructor::get_type() {
    return type;
}

}
