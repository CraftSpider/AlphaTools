
#include <iostream>
#include "at_tests"
#include "utils/strmanip.h"
#include "utils/format.h"
#include "test_format.h"

class Form {
public:
    std::string __format__(std::string) const {
        return "Formatted!";
    }
};

void ordinal_format() {
    ASSERT(util::format("{1:} {0:}", "world", "Hello") == "Hello world");
    ASSERT(util::format("{1:} == {}", 100, 200) == "200 == 100");
}

void int_format() {
    ASSERT(util::format("{}", 12345) == "12345");
    ASSERT(util::format("{0}", 12345) == "12345");
    
    ASSERT(util::format("{x}", 54321) == "d431");
    ASSERT(util::format("{x0}", 54321) == "0xd431");
    
    ASSERT(util::format("{X}", 54321) == "D431");
    ASSERT(util::format("{X0}", 54321) == "0xD431");
    
    ASSERT(util::format("{o}", 12345) == "30071");
    ASSERT(util::format("{o0}", 12345) == "0o30071");
}

void string_format() {
    ASSERT(util::format("{}", "test string") == "test string");
    ASSERT(util::format("{n}", "test string") == "11");
    
    ASSERT(util::format("{u}", "tEsT sTrInG") == "TEST STRING");
    ASSERT(util::format("{l}", "tEsT sTrInG") == "test string");
}

void bytes_format() {
    uchar bytes[] = {0x12, 0x34, 0x56, 0x78, 0x9A};
    
    ASSERT(util::format("{x0,7}", bytes) == "0x12");
    ASSERT(util::format("{X4,11}", bytes) == "0x23");
    
    ASSERT(util::format("{s3,6}", bytes) == "-7");
    ASSERT(util::format("{a3,6}", bytes) == "7");
}

void object_format() {
    // Can't assert 'this doesn't compile' so no more NoForm test
    Form* form = new Form();
    
    auto x = util::spec_handler<Form*>;
    x(std::string(), &form);
    
    ASSERT(util::format("{}", form) == "Formatted!");
    
    delete form;
}

void run_format_tests() {
    TEST(ordinal_format)
    TEST(int_format)
    TEST(string_format)
    TEST(bytes_format)
    TEST(object_format)
}
