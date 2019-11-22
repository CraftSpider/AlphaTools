
#include <sstream>
#include "tests/test.h"
#include "tests/test_case.h"

namespace testing {

std::string TestCase::get_name() {
    return name;
}

}
