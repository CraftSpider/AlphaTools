
#include <stdexcept>
#include "generic.h"

#ifdef LINUXCOMPAT
#include <unistd.h>
#include <climits>
#include <cxxabi.h>
#endif

#ifdef WINCOMPAT
#include <windows.h>
#include <dbghelp.h>
#include <lmcons.h>
#endif

std::string get_username() {
#ifdef LINUXCOMPAT
    char username[LOGIN_NAME_MAX + 1];
    getlogin_r(username, LOGIN_NAME_MAX + 1);
    return std::string(username);
#elif defined(WINCOMPAT)
    char username[UNLEN + 1];
    DWORD username_len = UNLEN + 1;
    GetUserName(username, &username_len);
    return std::string(username);
#else
    return std::getenv("USER");
#endif
}

std::string get_computer_name() {
#ifdef LINUXCOMPAT
    char hostname[HOST_NAME_MAX + 1];
    gethostname(hostname, HOST_NAME_MAX + 1);
    return std::string(hostname);
#elif defined(WINCOMPAT)
    char hostname[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD hostname_len = MAX_COMPUTERNAME_LENGTH + 1;
    GetComputerName(hostname, &hostname_len);
    return std::string(hostname);
#else
    return std::getenv("HOSTNAME");
#endif
}

std::string demangle(const std::string& name) {
#ifdef LINUXCOMPAT
    int status = 1;
    const char* str = abi::__cxa_demangle(name.c_str(), nullptr, nullptr, &status);
    if (status < 0) {
        throw std::runtime_error("Demangler name return failed");
    }
    std::string result = std::string(str);
    delete str;
    return result;
#elif defined(WINCOMPAT)
    static char symbolname[2048];
    symbolname[0] = '\0';
    DWORD length = UnDecorateSymbolName(name.c_str(), (PSTR)&symbolname, 2048, 0x2000);
    if (length == 0) {
        throw std::runtime_error("Demangler name return failed");
    }
    return std::string(symbolname);
#else
    return name;
#endif
}
