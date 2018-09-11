
#include <w32api/winsock.h>
#include <stdexcept>
#include <cygwin/in.h>
#include "socket.h"

class socket_error : std::runtime_error {
public:
    socket_error(std::string msg) : runtime_error(msg) {}
};

Socket::Socket(short domain, uint type) {
    this->domain = domain;
    this->type = type;
    
    sockfd = socket(domain, type, 0);
    if (sockfd == 0) {
        throw socket_error("Failed to create socket");
    }
}

void Socket::setopt() {

}

void Socket::bind(ushort port) {
    sockaddr_in *addr = new sockaddr_in();
    addr->sin_family = domain;
    addr->sin_addr.s_addr = INADDR_ANY;
    addr->sin_port = htons(port);
    
    this->addr = (sockaddr*)addr;
    
    if (::bind(sockfd, this->addr, sizeof(addr)) < 0) {
        throw socket_error("Failed to bind socket");
    }
}

void Socket::listen(uint backlog) {
    if (::listen(sockfd, backlog) < 0) {
        throw socket_error("Failed to listen to socket");
    }
}

void Socket::accept() {
    int size = sizeof(addr);
    accepted = ::accept(sockfd, addr, &size);
}

void Socket::recv() {
//    ::recv(accepted, buffer, );
}
