#pragma once

#ifdef _WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>
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

/**
 * \file socket.h
 * \brief Generic cross-platform sockets for C++
 */

namespace network {

/**
 * General error thrown by any socket failure
 */
class socket_error : public std::runtime_error {
public:
    
    /**
     * Construct a socket_error with the given message
     *
     * \param msg Message for this error
     */
    explicit socket_error(const std::string& msg);
    
};

/**
 * Error thrown if a socket can't be bound
 */
class bind_error : public socket_error {
    
    int errnum;
    
public:
    
    /**
     * Construct a new bind error. Takes the errnum result of the failure and a message
     *
     * \param errnum Errnum returned by failed function
     * \param msg Message of this error
     */
    explicit bind_error(int errnum, const std::string& msg);
    
};

/**
 * A struct representing a socket option
 */
struct SockOpt {
    
    std::string name;
    int sock_name;
    socklen_t length;
    
    static const SockOpt DEBUG, BROADCAST, REUSEADDR, KEEPALIVE, LINGER, OOBINLINE, SNDBUF, RCVBUF, DONTROUTE,
            RCVLOWAT, RCVTIMEO, SNDLOWAT, SNDTIMEO;
    
protected:
    
    /**
     * Construct a new SockOpt instance. Protected as all options are constructed by the library statically.
     *
     * \param name Human-readable name of the option
     * \param sock_name Actual value of the option
     * \param length Size of pointer passed to the option
     */
    SockOpt(const char* name, int sock_name, socklen_t length) noexcept;
    
};


/**
 * A struct representing an IP address
 */
struct IPAddr {
    std::string text;
    in_addr addr;
    
    /**
     * Construct a new IP Address from a string of the form "XXX.XXX.XXX.XXX"
     *
     * \param text String to construct from
     */
    explicit IPAddr(const std::string& text);
    
    /**
     * Construct a new IP Address from an in_addr struct
     *
     * \param addr Struct to construct from
     */
    explicit IPAddr(const in_addr& addr);
};

/**
 * A low level socket. In most cases, shouldn't use this
 */
class Socket {
    
    ushort domain;
    ulong sockfd;
    uint type;
    
    sockaddr* addr;
    
    /**
     * Protected constructor for a socket with an existing file descriptor
     *
     * \param sockfd Existing file descriptor
     * \param domain Domain of the socket, defaults to Internet
     * \param type Type of the socket, defaults to Stream
     */
    explicit Socket(ulong sockfd, ushort domain = AF_INET, uint type = SOCK_STREAM);

public:
    
    /**
     * Public constructor for a socket without an existing file descriptor
     *
     * \param domain Intended domain, defaults to Internet
     * \param type Intended type, defaults to Stream
     */
    explicit Socket(ushort domain = AF_INET, uint type = SOCK_STREAM);
    
    /**
     * Destruct a socket correctly
     */
    ~Socket();
    
    /**
     * Set a socket option, with option type and the new value
     *
     * \param option Option to set
     * \param val Value to set to
     */
    void setopt(SockOpt option, const void* val);
    
    /**
     * Get a socket option, with option type and a pointer to store the value in
     *
     * \param option Option to retrieve
     * \param val Pointer to store value in
     */
    void getopt(SockOpt option, void* val);
    
    /**
     * Bind this socket to a port
     *
     * \param port Port to bind to
     */
    void bind(ushort port);
    
    /**
     * Connect to an IP address by string on a given port
     *
     * \param ip IP address string, of the format "XXX.XXX.XXX.XXX"
     * \param port Port to connect on
     */
    void connect(const std::string& ip, ushort port);
    
    /**
     * Connect to an IP address by IPAddr instance
     *
     * \param ip IP address to connect to
     * \param port Port to connect on
     */
    void connect(IPAddr ip, ushort port);
    
    /**
     * Set this socket up to listen for incoming connections, with parameter for
     * allowed number of unaccepted connections
     *
     * \param backlog Maximum connection backlog
     */
    void listen(uint backlog);
    
    /**
     * Accept an incoming connection on the port this socket is bound to. Returns a new
     * socket representing the accepted connection
     *
     * \return Accepted connection socket
     */
    Socket accept();
    
    /**
     * Receive some number of bytes on this socket, defaults to just one byte. Returned
     * array must be deleted by the user
     *
     * \param size Number of bytes to retrieve.
     * \return Array of retrieved bytes
     */
    const char* recv(uint size = 1);
    
    /**
     * Send some number of bytes on this socket. Requires both the bytes array and
     * the length of the array, as there is no need for arrays to be null
     * terminated. Does not delete the accepted array.
     *
     * \param bytes Bytes array to send
     * \param length Length of the array
     */
    void send(const char* bytes, uint length);
    
    /**
     * Alias for shutdown with method 2
     */
    void close();
    
    /**
     * Tell the OS to free all or part of this socket, with parameter for how the socket closing
     * will be handled
     *
     * SHUT_RD: Receptions disallowed
     * SHUT_WR: Sending disallowed
     * SHUT_RDWR: Receptions and Sending disallowed
     *
     * \param how Which method to shutdown with
     */
    void shutdown(int how);
    
};

}
