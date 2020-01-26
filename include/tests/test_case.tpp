
#include "tests/test.h"

namespace testing {

template<typename T>
__TestCase<T>::__TestCase(T inst, const std::string& name) {
    this->instance = inst;
    this->name = name;
}

template<typename T>
__TestCase<T>::~__TestCase() {
    if constexpr (util::TypeFinder<T>::cls) {
        delete instance;
    }
}

template<typename T>
template<typename C, std::enable_if_t<util::TypeFinder<C>::function, int>>
void __TestCase<T>::__run() {
    try {
        (*this->instance)();
        __test_on_success(name);
    } catch (assertion_failure& e) {
        __test_on_failure(name, e);
    } catch (skip_test& e) {
        __test_on_skip(name, e);
    } catch (std::exception& e) {
        __test_on_error(name, e);
    }
}

template<typename T>
template<typename C, std::enable_if_t<util::TypeFinder<C>::cls, int>>
void __TestCase<T>::__run() {
    if (instance->skip_class()) {
        __test_on_skip(name, TestType::CLASS);
    } else {
        instance->before_class();
        try {
            instance->run();
            if (!instance->delegated) {
                __test_on_success(name, TestType::CLASS);
            }
        } catch (assertion_failure& e) {
            if (!instance->delegated) {
                __test_on_failure(name, e, TestType::CLASS);
            }
        } catch (skip_test& e) {
            __test_on_skip(name, e, TestType::CLASS);
        } catch (std::exception& e) {
            if (!instance->delegated) {
                __test_on_error(name, e, TestType::CLASS);
            }
        }
        instance->after_class();
    }
}

template<typename T>
void __TestCase<T>::run() {
    this->__run<T>();
}

}
