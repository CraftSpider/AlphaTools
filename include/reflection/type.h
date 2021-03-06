#pragma once

#include <string>
#include <vector>
#include <map>

/**
 * \file type.h
 * \brief Reflection support for type metadata
 */

namespace reflect {

// Forward refs
class Constructor;
class MemberProperty;
class MemberFunction;
class StaticProperty;
class StaticFunction;
class Destructor;
class Caster;

/**
 * \internal
 *
 * Class to get information about a type in a type-safe and well-formed way
 *
 * \tparam T Type to get info of
 */
template<typename T>
class MetaType {
public:
    
    /**
     * Get the raw name the type was registered with
     *
     * \return Raw type name
     */
    static std::string raw_name();
    
    /**
     * Get the name of the given type
     *
     * \return Type name
     */
    static std::string get_name();
    
};

/**
 * Class that represents a type in the reflection system. Contains all reflected information about the type,
 * and can be used to create and manage instances of the type
 *
 * \TODO: Add support for operators
 */
class Type final {
    
    std::string name;
    bool final;
    
    std::vector<Type*> parents;
    std::vector<Type*> children;
    
    std::vector<Constructor*> constructors;
    std::vector<MemberProperty*> member_properties;
    std::vector<MemberFunction*> member_functions;
    std::vector<StaticProperty*> static_properties;
    std::vector<StaticFunction*> static_functions;
    Destructor* destructor = nullptr;
    Caster* caster = nullptr;
    
    /**
     * Constructing new instances is managed by the library and is private
     *
     * \tparam T Associated real type
     * \param meta Meta to get info from
     */
    template<typename T>
    explicit Type(MetaType<T> meta);
    
    /**
     * As Types have a static lifetime, prevent external things from
     * deleting them
     */
    ~Type() = default;
    
    /**
     * Retrieve a static map of all names to Type instances
     *
     * \return Map of type names to Type instances
     */
    static std::map<std::string, Type*>& __type_map();

public:
    
    Type(Type&) = delete;
    
    Type(Type&&) = delete;
    
    /**
     * Get the Type associated with a given real type
     *
     * \tparam T Real type to get from
     * \return Associated Type instance
     */
    template<typename T>
    static Type* from();
    
    /**
     * Get the Type associated with a given variable pointer
     *
     * \tparam T Real type to get from
     * \return Associated type instance
     */
    template<typename T>
    static Type* from_instance(T*);
    
    /**
     * Get a Type instance by name. Not that `const` is always prefixed, and
     * things like `*` and `&` have no spaces before them, by convention
     *
     * \param name Name of the type to retrieve.
     * \return Associated type instance
     */
    static Type* from_name(const std::string& name);
    
    /**
     * Get a vector of types from a variadic list of parameters. Useful for argument list generation
     *
     * \tparam Args real types to get Type instances for
     * \return List of associated Type instances
     */
    template<typename... Args>
    static std::vector<Type*> from_list();
    
    /**
     * \internal
     *
     * Add a class as a parent of this class, used by the type declaration system
     *
     * \param parent Parent type to add
     */
    void __add_parent_class(Type* parent);
    
    /**
     * \internal
     *
     * Add a class as a child of this class, used by the type declaration system
     *
     * \param child Child type to add
     */
    void __add_child_class(Type* child);
    
    /**
     * \internal
     *
     * Add a constructor to this type, used by the type declaration system
     *
     * \param constructor Constructor to add
     */
    void __add_constructor(Constructor* constructor);
    
    /**
     * \internal
     *
     * Add a member property to this type, used by the type declaration system
     *
     * \param property Member property to add
     */
    void __add_member_property(MemberProperty* property);
    
    /**
     * \internal
     *
     * Add a member function to this type, used by the type declaration system
     *
     * \param function Member function to add
     */
    void __add_member_function(MemberFunction* function);
    
    /**
     * \internal
     *
     * Add a static property to this type, used by the type declaration system
     *
     * \param property Static property to add
     */
    void __add_static_property(StaticProperty* property);
    
    /**
     * \internal
     *
     * Add a static function to this type, used by the type declaration system
     *
     * \param function Static function to add
     */
    void __add_static_function(StaticFunction* function);
    
    /**
     * \internal
     *
     * Set the destructor for this type, used by the type declaration system
     *
     * \param destructor Destructor to set
     */
    void __set_destructor(Destructor* destructor);
    
    /**
     * \internal
     *
     * Set the caster for this type, used by the type declaration system
     *
     * \param caster Caster to set
     */
    void __set_caster(Caster* caster);
    
    /**
     * Get the name of this type
     *
     * \return Type name
     */
    const std::string& get_name();
    
    /**
     * Get whether this type is final
     *
     * \return Finality of type
     */
    bool is_final();
    
    /**
     * Get the associated type with a pointer added
     *
     * \return Type with one more pointer
     * \TODO: Make int& become int*& not int&*, second one is invalid because order matters
     */
    Type* add_pointer();
     
    /**
     * Get the associated type with a pointer removed
     *
     * \return Type with one fewer pointer
     */
    Type* remove_pointer();
    
    /**
     * Get the parent types for this type
     *
     * \return All parents of this type
     */
    const std::vector<Type*>& get_parents();
    
    /**
     * Get the child types for this type
     *
     * \return All children of this type
     */
    const std::vector<Type*>& get_children();
    
    /**
     * Get all registered constructors for this type
     *
     * \return Type constructors
     */
    const std::vector<Constructor*>& get_constructors();
    
    /**
     * Get a constructor for this type based on the arguments
     *
     * \param types Desired constructor arg types
     * \return Constructor or nullptr
     */
    Constructor* get_constructor(std::vector<Type*> types);
    
    /**
     * Get the default constructor for this type, if it exists
     *
     * \return Default constructor or nullptr
     */
    Constructor* get_default_constructor();
    
    /**
     * Get the copy constructor for this type, if it exists
     *
     * \return Copy constructor or nullptr
     */
    Constructor* get_copy_constructor();
    
    /**
     * Get the move constructor for this type, if it exists
     *
     * \return Move constructor or nullptr
     */
    Constructor* get_move_constructor();
    
    /**
     * Get all registered member properties for this type
     *
     * \return Type properties
     */
    const std::vector<MemberProperty*>& get_properties();
    
    /**
     * Get a property for this type based on its name
     *
     * \param name Name of the property
     * \return Member property or nullptr
     */
    MemberProperty* get_property(std::string name);
    
    /**
     * Get all registered member functions for this type
     *
     * \return Type functions
     */
    const std::vector<MemberFunction*>& get_functions();
    
    /**
     * Get member functions for this type based on their call types,
     * gets all functions that match that call signature
     *
     * \param types Types the function is called with
     * \return Member functions or nullptr
     */
    std::vector<MemberFunction*> get_functions(std::vector<Type*> types);
    
    /**
     * Get member functions for this type based on their name, gets all overloads
     * for a single function effectively
     *
     * \param name Name of the function
     * \return Member function or nullptr
     */
    std::vector<MemberFunction*> get_functions(std::string name);
    
    /**
     * Get a member function for this type based on its name and types
     *
     * \param name Name of the function
     * \param types Types the function is called with
     * \return Member function or nullptr
     */
    MemberFunction* get_function(std::string name, std::vector<Type*> types);
    
    /**
     * Get all registered static properties for this type
     *
     * \return Type static properties
     */
    const std::vector<StaticProperty*>& get_static_properties();
    
    /**
     * Get a static property for this type based on its name
     *
     * \param name Name of the static property
     * \return Static property or nullptr
     */
    StaticProperty* get_static_property(std::string name);
    
    /**
     * Get all registered static function for this type
     *
     * \return Type static functions
     */
    const std::vector<StaticFunction*>& get_static_functions();
    
    /**
     * Get a static function for this type based on its name
     *
     * \param name Name of the static function
     * \return Static function or nullptr
     */
    StaticFunction* get_static_function(std::string name);
    
    /**
     * Get the destructor for this type, if it is reflected
     *
     * \return Destructor or nullptr
     */
    Destructor* get_destructor();
    
    /**
     * Get the caster for this type, this will always exist
     *
     * \return Caster for the type
     */
    Caster* get_caster();
    
};

}

#include "type.tpp"
