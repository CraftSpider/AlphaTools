
#include "network/socket.h"

namespace network {

socket_error::socket_error(const std::string &msg) : runtime_error(msg) {}


bind_error::bind_error(int errnum, const std::string &msg) : socket_error(msg) {
    this->errnum = errnum;
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

SockOpt::SockOpt(const char* name, int sock_name, socklen_t length) noexcept {
    this->name = name;
    this->sock_name = sock_name;
    this->length = length;
}


IPAddr::IPAddr(const std::string &text) : addr() {
    this->text = text;
    inet_pton(AF_INET, text.c_str(), &addr);
}


IPAddr::IPAddr(const in_addr& addr) : addr() {
    char _text[16];
    this->text = inet_ntop(AF_INET, &addr, _text, 16);
    this->addr = addr;
}


static void __setup_sockets() {
#if defined(_WIN32)
    WSADATA wsadata;
    int result;
    
    result = WSAStartup(MAKEWORD(2, 2), &wsadata);
    if (result != 0) {
        throw socket_error("Socket initialization failed");
    }
#endif
}


static void __teardown_sockets() {
#if defined(_WIN32)
    WSACleanup();
#endif
}


Socket::Socket(ulong sockfd, ushort domain, uint type) {
    __setup_sockets();
    this->addr = nullptr;
    this->sockfd = sockfd;
    this->domain = domain;
    this->type = type;
}

Socket::Socket(ushort domain, uint type) {
    __setup_sockets();
    this->addr = nullptr;
    this->domain = domain;
    this->type = type;
    
    sockfd = (ulong)socket(domain, type, 0);
    if (sockfd == 0) {
        throw socket_error("Failed to create socket");
    }
}

Socket::~Socket() {
    delete addr;
    __teardown_sockets();
}

void Socket::setopt(SockOpt option, const void *val) {
    setsockopt(sockfd, SOL_SOCKET, option.sock_name, val, option.length);
}

void Socket::getopt(SockOpt option, void* val) {
    getsockopt(sockfd, SOL_SOCKET, option.sock_name, val, &option.length);
}

void Socket::bind(ushort port) {
    sockaddr_in* addr_in = new sockaddr_in();
    addr_in->sin_family = domain;
    addr_in->sin_addr.s_addr = INADDR_ANY;
    addr_in->sin_port = htons(port);
    
    this->addr = reinterpret_cast<sockaddr*>(addr_in);
    
    if (::bind(sockfd, this->addr, sizeof(*addr_in)) < 0) {
        throw bind_error(errno, "Failed to bind socket");
    }
}

void Socket::connect(const std::string &ip, ushort port) {
    connect(IPAddr(ip), port);
}

void Socket::connect(IPAddr ip, ushort port) {
    sockaddr_in* addr_in = new sockaddr_in();
    addr_in->sin_family = domain;
    addr_in->sin_addr = ip.addr;
    addr_in->sin_port = htons(port);
    
    this->addr = reinterpret_cast<sockaddr*>(addr_in);
    
    if (::connect(sockfd, this->addr, sizeof(*addr_in)) < 0) {
        throw socket_error("Failed to connect socket");
    }
}

void Socket::listen(uint backlog) {
    if (::listen(sockfd, backlog) < 0) {
        throw socket_error("Failed to listen to socket");
    }
}

Socket Socket::accept() {
    socklen_t size = (socklen_t)sizeof(*addr);
    ulong accepted = (ulong)::accept(sockfd, addr, &size);
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
