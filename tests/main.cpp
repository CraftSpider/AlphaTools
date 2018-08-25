
#include "test.h"

int main(int argc, char **argv) {
    run_tests();
    
    std::cout << "Alpha Utils testing complete. Results:\n";
    std::cout << "Successes: " << Results::successes << " Failures: " << Results::failures;
    std::cout << " Errors: " << Results::errors << " Skipped: " << Results::skipped << "\n";
    
}