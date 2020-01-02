
#include "tests/assertion.h"

namespace testing {

void assert(bool statement, const std::string& message) {
    if (!statement)
        throw assertion_failure(message);
}

void fail(const std::string& message) {
    throw assertion_failure(message);
}

}
