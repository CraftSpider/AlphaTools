#pragma once

#include <sys/socket.h>
#include "types.h"

/**
 * A low level socket. In most cases, shouldn't use this
 */
class Socket {
    
    short domain;
    int sockfd, accepted;
    uint type;
    
    sockaddr *addr;

public:
    
    Socket(short domain = AF_INET, uint type = SOCK_STREAM);
    
    void setopt();
    void bind(ushort port);
    void listen(uint backlog);
    void accept();
    void recv();
    
};
