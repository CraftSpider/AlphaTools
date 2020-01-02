
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

template<typename T, typename U>
void assert_files_equal(T& first, U& second, std::string message) {
    static constexpr int buf_size = 256;
    
    first.seekg(0, std::ios::end);
    second.seekg(0, std::ios::end);
    
    if (first.tellg() != second.tellg())
        throw assertion_failure(message);
    
    first.seekg(0);
    second.seekg(0);
    
    char f_str[buf_size] = {};
    char s_str[buf_size] = {};
    while (first.good() && second.good()) {
        first.read(f_str, buf_size);
        second.read(s_str, buf_size);
        
        if (first.good() != second.good())
            throw assertion_failure(message);
        for (int i = 0; i < buf_size; ++i) {
            if (f_str[i] != s_str[i])
                throw assertion_failure(message);
            f_str[i] = 0;
            s_str[i] = 0;
        }
    }
}

template<typename T, typename U>
void assert_files_not_equal(T& first, U& second, std::string message) {
    static constexpr int buf_size = 256;
    
    first.seekg(0, std::ios::end);
    second.seekg(0, std::ios::end);
    
    if (first.tellg() != second.tellg())
        return;
    
    first.seekg(0);
    second.seekg(0);
    
    char f_str[buf_size] = {};
    char s_str[buf_size] = {};
    while (first.good() && second.good()) {
        first.read(f_str, buf_size);
        second.read(s_str, buf_size);
        
        if (first.good() != second.good())
            return;
        
        for (int i = 0; i < buf_size; ++i) {
            if (f_str[i] != s_str[i])
                return;
            f_str[i] = 0;
            s_str[i] = 0;
        }
    }
    
    throw assertion_failure(message);
}

template<typename T, typename ...Args, typename K>
void assert_throws(K callable, Args... args) {
    try {
        callable(args...);
        fail(std::string("Callable did not throw ") + typeid(T).name());
    } catch(T&) {}
}

template<typename T, typename... Args, typename K>
void assert_throws(const std::string& message, K callable, Args... args) {
    try {
        callable(args...);
        fail(message);
    } catch(T&) {}
}

}
