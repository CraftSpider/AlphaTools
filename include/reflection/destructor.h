#pragma once

#include "type.h"
#include "variant.h"

namespace reflect {

typedef void(*DestructFuncRef)(Variant);

template<typename T>
class DestructorMeta {
public:
    
    static void destruct(Variant instance);
    
    static DestructFuncRef get_destruct_func();
    
};

class Destructor {
    
    Type *type;
    
    DestructFuncRef ptr;
    
    template<typename T>
    explicit Destructor(DestructorMeta<T> meta);
    
public:
    
    template<typename T>
    static Destructor& from();
    
    void destruct(Variant instance);
    
    Type* get_type();
    
};

}

#include "destructor.tpp"
