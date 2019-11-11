#pragma once

namespace testing {

class TestCase {
public:
    virtual void run() = 0;
};

template<typename T>
class __TestCase : public TestCase {
    
    T instance;
    std::string name;

public:
    
    __TestCase(T inst, const std::string& name);
    
    template<typename C, std::enable_if_t<util::TypeFinder<C>::function, int> = 0>
    void __run();
    
    template<typename C, std::enable_if_t<util::TypeFinder<C>::pointer, int> = 0>
    void __run();
    
    template<typename C, std::enable_if_t<util::TypeFinder<C>::method, int> = 0>
    void __run();
    
    void run() override;
    
};

}

#include "test_case.tpp"
