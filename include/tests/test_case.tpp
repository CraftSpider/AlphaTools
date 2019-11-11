
#include "tests/test.h"

namespace testing {

template<typename T>
__TestCase<T>::__TestCase(T inst, const std::string& name) {
    this->instance = inst;
    this->name = name;
}

template<typename T>
template<typename C, std::enable_if_t<util::TypeFinder<C>::function, int>>
void __TestCase<T>::__run() {
    try {
        (*this->instance)();
        testing::__test_on_success(name);
    } catch (testing::assertion_failure &e) {
        testing::__test_on_failure(name, e);
    } catch (testing::skip_test &e) {
        testing::__test_on_skip(name, e);
    } catch (std::exception &e) {
        testing::__test_on_error(name, e);
    }
}

template<typename T>
template<typename C, std::enable_if_t<util::TypeFinder<C>::pointer, int>>
void __TestCase<T>::__run() {
    if (instance->skip_class()) {
        testing::__test_on_skip(name, testing::CLASS);
    } else {
        instance->before_class();
        try {
            instance->run();
            if (!instance->delegated) {
                testing::__test_on_success(name, testing::CLASS);
            }
        } catch (testing::assertion_failure &e) {
            if (!instance->delegated) {
                testing::__test_on_failure(name, e, testing::CLASS);
            }
        } catch (testing::skip_test &e) {
            testing::__test_on_skip(name, e, testing::CLASS);
        } catch (std::exception &e) {
            if (!instance->delegated) {
                testing::__test_on_error(name, e, testing::CLASS);
            }
        }
        instance->after_class();
    }
}

template<typename T>
template<typename C, std::enable_if_t<util::TypeFinder<C>::method, int>>
void __TestCase<T>::__run() {}

template<typename T>
void __TestCase<T>::run() {
    this->__run<T>();
}

}
