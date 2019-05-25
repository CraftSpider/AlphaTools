
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

}
