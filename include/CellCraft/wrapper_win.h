#ifndef WRAPPER_WIN_H
#define WRAPPER_WIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <stdint.h>
#include <errno.h>


// ssize_t is not defined in windows
#if SIZE_MAX == UINT_MAX
typedef int ssize_t; /* common 32 bit case */
#define SSIZE_MIN INT_MIN
#define SSIZE_MAX INT_MAX
#elif SIZE_MAX == ULLONG_MAX
typedef long long ssize_t; /* windows 64 bits */
#define SSIZE_MIN LLONG_MIN
#define SSIZE_MAX LLONG_MAX
#else
#error platform has exotic SIZE_MAX
#endif

// Socket type
#define SHUT_RD SD_RECEIVE
#define SHUT_WR SD_SEND
#define SHUT_RDWR SD_BOTH

#define MSG_NOSIGNAL 0

typedef int socklen_t;

// Endian swapping definitions
#define __builtin_bswap16(x) _byteswap_ushort(x)
#define __builtin_bswap32(x) _byteswap_ulong(x)
#define __builtin_bswap64(x) _byteswap_uint64(x)

// Misc functions
static inline void U_wrapperStart()
{
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
}
static inline void U_wrapperEnd()
{
    WSACleanup();
}

static inline void U_sleep(int msec)
{
    Sleep(msec);
}
static inline uint64_t U_millis()
{
    LARGE_INTEGER tick, tps;
    QueryPerformanceFrequency(&tps);
    QueryPerformanceCounter(&tick);
    int msPassed = (tick.QuadPart) * 1000 / tps.QuadPart;
    return msPassed;
}
// Networking functions
static inline int U_socket(int domain, int type, int protocol)
{
    return socket(domain, type, protocol);
}

static inline int U_setsockopt(int sockfd, int level, int optname, const void *optval, int optlen)
{
    return setsockopt(sockfd, level, optname, optval, optlen);
}

static inline int U_setsocknonblock(int sockfd)
{
    u_long iMode = 1;
    return ioctlsocket(sockfd, FIONBIO, &iMode);
}

static inline int U_bind(int sockfd, const struct sockaddr *addr, int addrlen)
{
    return bind(sockfd, addr, addrlen);
}

static inline int U_listen(int sockfd, int backlog)
{
    return listen(sockfd, backlog);
}

static inline int U_select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout)
{
    return select(nfds, readfds, writefds, exceptfds, timeout);
}

static inline int U_accept(int sockfd, struct sockaddr *addr, int *addrlen)
{
    return accept(sockfd, addr, addrlen);
}

static inline int U_getpeername(int sockfd, struct sockaddr *addr, int *addrlen)
{
    return getpeername(sockfd, addr, addrlen);
}

static inline struct hostent *U_gethostbyname(const char *name)
{
    return gethostbyname(name);
}

static inline char *U_inet_ntoa(struct in_addr in)
{
    return inet_ntoa(in);
}

static inline int U_recv(SOCKET sockfd, char *buf, int len, int flags)
{
    return recv(sockfd, buf, len, flags);
}

static inline int U_send(SOCKET sockfd, const void *buf, size_t len, int flags)
{
    return send(sockfd, buf, len, flags);
}

static inline int U_connect(SOCKET sockfd, const struct sockaddr *addr, int addrlen)
{
    return connect(sockfd, addr, addrlen);
}

static inline int U_close(SOCKET fd)
{
    return closesocket(fd);
}

static inline int U_shutdown(SOCKET sockfd, int how)
{
    return shutdown(sockfd, how);
}
// Memory function
static inline void *U_malloc(size_t size)
{
    return malloc(size);
}

static inline void *U_calloc(size_t nmemb, size_t size)
{
    return calloc(nmemb, size);
}

static inline void *U_realloc(void *ptr, size_t size)
{
    return realloc(ptr, size);
}

static inline void U_free(void *ptr)
{
    free(ptr);
}
#endif