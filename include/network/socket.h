#pragma once

// TODO: Move this stuff to general somehow?
#ifdef _WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>
#define setsockopt(s, level, optname, optval, oplen) setsockopt(s, level, optname, (const char*)optval, oplen)
#define getsockopt(s, level, optname, optval, oplen) getsockopt(s, level, optname, (char*)optval, oplen)
#elif defined(__CYGWIN__)
#include <cygwin/in.h>
#include <arpa/inet.h>
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#endif

#include <string>
#include <stdexcept>
#include "types.h"

namespace network {

class socket_error : public std::runtime_error {
public:
    explicit socket_error(const std::string& msg);
};

class bind_error : public socket_error {
    int errnum;
public:
    explicit bind_error(int errnum, const std::string& msg);
};

struct SockOpt {
    
    std::string name;
    int sock_name;
    socklen_t length;
    
    static const SockOpt DEBUG, BROADCAST, REUSEADDR, KEEPALIVE, LINGER, OOBINLINE, SNDBUF, RCVBUF, DONTROUTE,
            RCVLOWAT, RCVTIMEO, SNDLOWAT, SNDTIMEO;
    
protected:
    
    SockOpt(const std::string& name, int sock_name, socklen_t length);
    
};


struct IPAddr {
    std::string text;
    in_addr addr;
    
    explicit IPAddr(const std::string& text);
    
    explicit IPAddr(const in_addr& addr);
};

/**
 * A low level socket. In most cases, shouldn't use this
 */
class Socket {
    
    explicit Socket(ulong sockfd, ushort domain = AF_INET, uint type = SOCK_STREAM);
    
    ushort domain;
    ulong sockfd;
    uint type;
    
    sockaddr* addr;

public:
    
    explicit Socket(ushort domain = AF_INET, uint type = SOCK_STREAM);
    ~Socket();
    
    void setopt(SockOpt option, const void* val);
    void getopt(SockOpt option, void* val);
    
    void bind(ushort port);
    
    void connect(const std::string& ip, ushort port);
    void connect(IPAddr ip, ushort port);
    
    void listen(uint backlog);
    Socket accept();
    const char* recv(uint size = 1);
    void send(const char* bytes, uint length);
    
    void close();
    void shutdown(int how);
    
};

}
