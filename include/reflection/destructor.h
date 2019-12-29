#pragma once

#include "type.h"
#include "variant.h"

namespace reflect {

typedef void(*DestructFuncRef)(void*);

template<typename T>
class DestructorMeta {
public:
    
    static void destruct(typename std::remove_reference_t<T>* instance);
    
    static DestructFuncRef get_destruct_func();
    
};

class Destructor final {
    
    Type *type;
    
    DestructFuncRef ptr;
    
    template<typename T>
    explicit Destructor(DestructorMeta<T> meta);
    
public:
    
    Destructor(Destructor&) = delete;
    Destructor(Destructor&&) = delete;
    
    template<typename T>
    static Destructor& from();
    
    void destruct(Variant instance);
    
    void unsafe_destruct(void* instance);
    
    Type* get_type();
    
};

}

#include "destructor.tpp"
