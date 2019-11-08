
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

#include "network/socket.h"
#include <thread>

void serv_socket() {
    
    network::Socket soc = network::Socket();
    int val = 1;
    soc.setopt(network::SockOpt::REUSEADDR, &val);
    soc.bind(8081);
    soc.listen(2);
    network::Socket accepted = soc.accept();
    
    const char* stuff = accepted.recv(6);
    for (uint i = 0; i < 6; ++i) {
        std::cout << stuff[i];
    }
    std::cout << std::endl;
    delete stuff;
    
    accepted.send("world", 6);
}

void client_socket() {
    
    network::Socket soc = network::Socket();
    soc.connect("127.0.0.1", 8081);
    soc.send("hello", 6);
    
    const char* stuff = soc.recv(6);
    for (uint i = 0; i < 6; ++i) {
        std::cout << stuff[i];
    }
    std::cout << std::endl;
    delete stuff;
}

int main(int argc, char **argv) {
//    std::thread serv(serv_socket);
//    std::thread client(client_socket);
//
//    serv.join();
//    client.join();
//
//    return 0;
	
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
    
    return testing::run_tests() & 0b011u;
}
