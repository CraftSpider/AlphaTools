
#include "reflection/destructor.h"

namespace reflect {

void Destructor::destruct(void* instance) {
    ptr(instance);
}

Type* Destructor::get_type() {
    return type;
}

}
