
#include <iostream>
#include "test_format.h"
#include "format.h"


class Huh : Formattable {
public:
    std::string __format__(std::string spec) override {
        return "Formatted!";
    }
};


void run_format_tests() {
    std::cout << format("{o}", new Huh()) << std::endl;
}