
#include "tests/assertion.h"

namespace testing {

void assert(bool statement, std::string message) {
    if (!statement)
        throw assertion_failure(message);
}

void fail(std::string message) {
    throw assertion_failure(message);
}

}
