
namespace testing {

template<typename T>
void assert_equal(T first, T second, std::string message) {
    if (!(first == second))
        throw assertion_failure(message);
}

template<typename T>
void assert_equal(T* first, T* second, std::string message) {
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
    if (!(*first != *second))
        throw assertion_failure(message);
}

template<typename T, typename K>
void assert_throws(K callable, std::string message) {
    try {
        callable();
        fail(message);
    } catch (T &e) {}
}

template<typename T, typename A, typename K>
void assert_throws(K callable, A arg, std::string message) {
    try {
        callable(arg);
        fail(message);
    } catch (T &e) {}
}

template<typename T, typename A, typename B, typename K>
void assert_throws(K callable, A arg1, B arg2, std::string message) {
    try {
        callable(arg1, arg2);
        fail(message);
    } catch (T &e) {}
}

}
