
namespace testing {

template<typename T>
void assert_equal(T first, T second, std::string message) {
    if (!(first == second))
        throw assertion_failure(message);
}

template<typename T>
void assert_equal(T* first, T* second, std::string message) {
    if (first == nullptr && second == nullptr)
        return;
    if (first == nullptr || second == nullptr)
        throw assertion_failure(message);
    
    if (!(*first == *second))
        throw assertion_failure(message);
}

template<typename T>
void assert_not_equal(T first, T second, std::string message) {
    if (!(first != second))
        throw assertion_failure(message);
}

template<typename T>
void assert_not_equal(T* first, T* second, std::string message) {
    if (first == nullptr && second == nullptr)
        throw assertion_failure(message);
    if (first == nullptr || second == nullptr)
        return;
    
    if (!(*first != *second))
        throw assertion_failure(message);
}

template<typename T, typename ...Args, typename K>
void assert_throws(K callable, Args... args) {
    try {
        callable(args...);
        fail(std::string("Callable did not throw ") + typeid(T).name());
    } catch(T&) {}
}

template<typename T, typename ...Args, typename K>
void assert_throws(std::string message, K callable, Args... args) {
    try {
        callable(args...);
        fail(message);
    } catch(T&) {}
}

}
