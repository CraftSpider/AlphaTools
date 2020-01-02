#pragma once

#include "type.h"

/**
 * \file variant.h
 * \brief A generic container for a value of any type. Can refcount itself or not
 */

namespace reflect {

/**
 * Class that represents an instance of any type. Can hold any kind of type, and is used for
 * most reflection operations as it is still type-safe. May own the instance, in which case
 * the pointer is refcounted and deleted once all referents are deleted.
 */
class Variant final {
    
    static std::map<void*, size_t> refcount;
    
    Type* type = nullptr;
    void* data = nullptr;
    bool owned = false;
    
    /**
     * Constructor is private, as Variants should only be created through the factories below
     */
    Variant() = default;
    
    /**
     * Increase the reference count for a pointer by 1
     * Addes to the map if it isn't currently in it
     *
     * \param data Pointer to count
     */
    static void increment_refcount(void* data);
    
    /**
     * Decrease the reference count for a pointer by 1
     * Deletes from the map if count hits 0
     *
     * \param data Pointer to count
     */
    static void decrement_refcount(void* data);
    
    /**
     * Get the reference count for a pointer
     * Returns 0 if the pointer isn't in the map
     *
     * \param data Pointer to count
     * \return Current pointer count
     */
    static size_t get_refcount(void* data);

public:
    
    /**
     * Copy construct a variant. Will increase the refcount if the pointer is owned
     *
     * \param other Variant to copy
     */
    Variant(const Variant& other);
    
    /**
     * Move construct a variant. Will not change the refcount, but will prevent it from
     * decreasing if the pointer is owned
     *
     * \param other Variant to move
     */
    Variant(Variant&& other) noexcept;
    
    /**
     * Delete a variant. Will delete the associated data if refcount hits 0 and the data
     * is owned by the Variant
     */
    ~Variant();
    
    /**
     * Construct a variant from a pointer to an object, not owned
     *
     * \tparam T Type of the pointer
     * \param obj Pointer to borrow
     * \return New variant instance
     */
    template<typename T>
    static Variant from_ptr(T* obj);
    
    /**
     * Construct a variant from a reference to an object, not owned
     *
     * \tparam T Type of the reference
     * \param obj Object to borrow
     * \return New variant instance
     */
    template<typename T>
    static Variant from_ref(T& obj);
    
    /**
     * Construct a variant from a copy of an object, owned
     *
     * \tparam T Type of the object
     * \param obj Object to take
     * \return New variant instance
     */
    template<typename T>
    static Variant from_instance(T obj);
    
    /**
     * Construct a variant from a return type, owned or not depending on the type
     * If the type is reference or pointer, Variant is unowned. Otherwise, the Variant
     * owns the data
     *
     * \tparam T Type of the object
     * \param obj Object to create from
     * \return New variant instance
     */
    template<typename T>
    static Variant from_return(T obj);
    
    /**
     * Construct a variant with no data from a type
     *
     * \param type Type of Variant
     * \return New variant instance
     */
    static Variant from_type(Type* type);
    
    /**
     * Construct a variant with data from a type and void pointer, unowned
     *
     * \param type Type of the Variant
     * \param data Data for the Variant
     * \return New variant instance
     */
    static Variant from_pair(Type* type, void* data);
    
    /**
     * Construct a variant with data from a type and void pointer, owned
     *
     * \param type Type of the variant
     * \param data Data to take ownership of
     * \return New variant instance
     */
    static Variant from_pair_owned(Type* type, void* data);
    
    /**
     * Get the type of the data stored in this variant
     *
     * \return Variant type
     */
    Type* get_type();
    
    /**
     * Get the value of this variant as a void pointer, no type safety is performed
     *
     * \return Raw data pointer
     */
    void* get_value_unsafe();
    
    /**
     * Get the value contained in this Variant as a pointer
     * Warning: If this Variant owns the pointer, for example in the case of the result of a construct call,
     * then the pointer will only live as long as this Variant does. Either copy the value, or use take_value_ptr.
     *
     * \tparam T Type to retrieve pointer as
     * \return Pointer to instance of type T
     */
    template<typename T>
    typename std::remove_reference_t<T>* get_value_ptr();
    
    /**
     * Get the value contained in this Variant as a reference
     * Same warning as the above
     *
     * \tparam T Type to retrieve reference as
     * \return Reference to instance of type T
     */
    template<typename T>
    typename std::remove_reference_t<T>& get_value_ref();
    
    /**
     * Get the value of this variant as a void pointer, no type safety is performed
     * If the value is owned, the variant will release ownership
     *
     * \return Raw data pointer
     */
    void* take_value_unsafe();
    
    /**
     * Get the value contained in this variant as a pointer
     * If the value is owned, the variant will release ownership
     *
     * \tparam T Type to retrieve pointer as
     * \return Pointer to instance of type T
     */
    template<typename T>
    typename std::remove_reference_t<T>* take_value_ptr();
    
    /**
     * Get the value contained in this variant as a reference
     * If the value is owned, the variant will release ownership
     *
     * \tparam T Type to retrieve reference as
     * \return Reference to instance of type T
     */
    template<typename T>
    typename std::remove_reference_t<T>& take_value_ref();
    
    /**
     * Get a copy of the value contained in this variant. Doesn't have a `take_` variant
     * as a copy is returned, which is uncontrolled by the Variant system
     *
     * \tparam T Type to retrieve copy as
     * \return New copy of contained data
     */
    template<typename T>
    T get_value();
    
    /**
     * Check whether this variant owns its contained data, meaning that the data is refcounted,
     * and deleted once all referring variants are deleted
     *
     * \return Whether data is owned
     */
    bool get_owned();
    
};

}

#include "variant.tpp"
