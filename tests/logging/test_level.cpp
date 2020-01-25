
#include <at_tests>
#include <at_logging>

#include "test_level.h"

using namespace logging;

Level* level_null;
Level* level_1;
Level* level_2;
Level* level_3;
Level* level_4;

void __build_level_ptrs() {
    level_null = new Level();
    level_1 = new Level(111, "TestLevel");
    level_2 = new Level(111, "TestLevel");
    level_3 = new Level(121, "TestLevel2");
    level_4 = new Level(101, "TestLevel3");
}

void test_level_construct() {
    ASSERT(level_null->get_name() == "NULL");
    ASSERT(level_null->get_priority() == 0);
    
    ASSERT(level_1->get_name() == "TestLevel");
    ASSERT(level_1->get_priority() == 111);
}

void test_level_compare() {
    ASSERT(*level_1 == *level_2);
    ASSERT(*level_1 != *level_3);
    
    ASSERT(*level_1 < *level_3);
    ASSERT(*level_4 <= *level_1);
    
    ASSERT(*level_3 > *level_1);
    ASSERT(*level_1 >= *level_4);
}

void test_level_cast() {
    ASSERT((std::string)*level_1 == level_1->get_name());
    ASSERT((std::string)*level_1 == "TestLevel");
}

void run_level_tests() {
    __build_level_ptrs();
    TEST(test_level_construct)
    TEST(test_level_compare)
    TEST(test_level_cast)
}
