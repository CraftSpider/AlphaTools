
#include <sstream>
#include <thread>
#include "at_tests"
#include "network/socket.h"

static std::stringstream* stream;

void serv_socket() {
    network::Socket soc = network::Socket();
    int val = 1;
    soc.setopt(network::SockOpt::REUSEADDR, &val);
    soc.bind(8081);
    soc.listen(2);
    network::Socket accepted = soc.accept();
    
    const char* stuff = accepted.recv(7);
    int i = 0;
    do {
        *stream << stuff[i];
        i++;
    } while (stuff[i] != '\0');
    delete stuff;
    
    accepted.send("world", 6);
}

void client_socket() {
    network::Socket soc = network::Socket();
    soc.connect("127.0.0.1", 8081);
    soc.send("hello ", 7);
    
    const char* stuff = soc.recv(6);
    int i = 0;
    do {
        *stream << stuff[i];
        i++;
    } while (stuff[i] != '\0');
    delete stuff;
}

void test_sockets() {
    stream = new std::stringstream();
    
    std::thread serv(serv_socket);
    std::thread client(client_socket);

    serv.join();
    client.join();
    
    ASSERT(stream->str() == "hello world");
}

void run_socket_tests() {
    TEST(test_sockets)
}
