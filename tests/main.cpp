
#include "at_tests"

#include "test_algorithms.h"
#include "test_arrays.h"
#include "test_bytes.h"
#include "test_strmanip.h"
#include "test_logging.h"
#include "test_format.h"
#include "test_console.h"
#include "test_test.h"
#include "test_io.h"
#include "test_generic.h"
#include "test_sfinae.h"
#include "test_matrix.h"
#include "test_socket.h"
#include "test_memory.h"

#include "reflection/test_constructor.h"
#include "reflection/test_type.h"
#include "reflection/test_reflection.h"

int main(int argc, char **argv) {
	testing::setup_tests(argc, argv);
	
	TEST_FILE(test)
    TEST_FILE(algorithms)
    TEST_FILE(arrays)
    TEST_FILE(bytes)
    TEST_FILE(strmanip)
    TEST_FILE(logging)
    TEST_FILE(format)
    TEST_FILE(console)
    TEST_FILE(io)
    TEST_FILE(generic)
    TEST_FILE(sfinae)
    TEST_FILE(matrix)
    TEST_FILE(socket)
    TEST_FILE(memory)
    TEST_FILE(constructor)
    TEST_FILE(type)
    TEST_FILE(reflection)
    
    int result = (int)(testing::run_tests() & 0b011u);
    
	testing::teardown_tests();
	
    return result;
}
