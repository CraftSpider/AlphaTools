
#include "network/socket.h"

#include <iostream>

namespace network {

socket_error::socket_error(const std::string &msg) : runtime_error(msg) {}

bind_error::bind_error(int errnum, const std::string &msg) : socket_error(msg) {
    std::cout << errnum << std::endl;
}

const SockOpt SockOpt::DEBUG = SockOpt("Debug", SO_DEBUG, sizeof(int));
const SockOpt SockOpt::BROADCAST = SockOpt("Broadcast", SO_BROADCAST, sizeof(int));
const SockOpt SockOpt::REUSEADDR = SockOpt("Reuse Address", SO_REUSEADDR, sizeof(int));
const SockOpt SockOpt::KEEPALIVE = SockOpt("Keep Alive", SO_KEEPALIVE, sizeof(int));
const SockOpt SockOpt::LINGER = SockOpt("Linger", SO_LINGER, sizeof(linger));
const SockOpt SockOpt::OOBINLINE = SockOpt("Out of Band inline", SO_OOBINLINE, sizeof(int));
const SockOpt SockOpt::SNDBUF = SockOpt("Send Buffer Size", SO_SNDBUF, sizeof(int));
const SockOpt SockOpt::RCVBUF = SockOpt("Receive Buffer Size", SO_RCVBUF, sizeof(int));
const SockOpt SockOpt::DONTROUTE = SockOpt("Don't Route", SO_DONTROUTE, sizeof(int));
const SockOpt SockOpt::RCVLOWAT = SockOpt("Receive Low Accept", SO_RCVLOWAT, sizeof(int));
const SockOpt SockOpt::RCVTIMEO = SockOpt("Receive Timeout", SO_RCVTIMEO, sizeof(timeval));
const SockOpt SockOpt::SNDLOWAT = SockOpt("Send Low Accept", SO_SNDLOWAT, sizeof(int));
const SockOpt SockOpt::SNDTIMEO = SockOpt("Send Timeout", SO_SNDTIMEO, sizeof(timeval));

Socket::Socket(int sockfd, ushort domain, uint type) {
    this->sockfd = sockfd;
    this->domain = domain;
    this->type = type;
}

Socket::Socket(ushort domain, uint type) {
    this->domain = domain;
    this->type = type;
    
    sockfd = socket(domain, type, 0);
    if (sockfd == 0) {
        throw socket_error("Failed to create socket");
    }
}

void Socket::setopt(SockOpt option, const void *val) {
    setsockopt(sockfd, SOL_SOCKET, option.sock_name, val, option.length);
}

void* Socket::getopt(SockOpt option, void* val) {
    getsockopt(sockfd, SOL_SOCKET, option.sock_name, val, &option.length);
}

void Socket::bind(ushort port) {
    sockaddr_in *addr = new sockaddr_in();
    addr->sin_family = domain;
    addr->sin_addr.s_addr = INADDR_ANY;
    addr->sin_port = htons(port);
    
    this->addr = (sockaddr*)addr;
    
    if (::bind(sockfd, this->addr, sizeof(*addr)) < 0) {
        throw bind_error(errno, "Failed to bind socket");
    }
}

void Socket::connect(const std::string &ip, ushort port) {
    connect(IPAddr(ip), port);
}

void Socket::connect(IPAddr ip, ushort port) {
    
    sockaddr_in *addr = new sockaddr_in();
    addr->sin_family = domain;
    addr->sin_addr = ip.addr;
    addr->sin_port = htons(port);
    
    this->addr = (sockaddr*)addr;
    
    if (::connect(sockfd, this->addr, sizeof(*addr)) < 0) {
        throw socket_error("Failed to connect socket");
    }
}

void Socket::listen(uint backlog) {
    if (::listen(sockfd, backlog) < 0) {
        throw socket_error("Failed to listen to socket");
    }
}

Socket Socket::accept() {
    int size = sizeof(*addr);
    int accepted = ::accept(sockfd, addr, &size);
    return Socket(accepted, domain, type);
}

const char* Socket::recv(uint size) {
    char *buffer = new char[size];
    ::recv(sockfd, buffer, size, 0);
    return buffer;
}

void Socket::send(const char *bytes, uint length) {
    ::send(sockfd, bytes, length, 0);
}

void Socket::close() {
    ::shutdown(sockfd, 2);
}

void Socket::shutdown(int how) {
    ::shutdown(sockfd, how);
}

}
