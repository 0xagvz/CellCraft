#ifndef WRAPPER_PS3_H
#define WRAPPER_PS3_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>

#include <sys/systime.h>
#include <net/socket.h>
#include <net/select.h>
#include <net/netdb.h>
#include <net/net.h>
#include <arpa/inet.h>

#ifndef MSG_NOSIGNAL
#define MSG_NOSIGNAL 0
#endif

#ifndef TCP_NODELAY
#define TCP_NODELAY 1
#endif
#include <sys/memory.h>

#undef FD_ZERO
#undef FD_SET
#undef FD_CLR
#undef FD_ISSET
static inline void U_ps3_fd_zero(fd_set *s)
{
    unsigned char *p = (unsigned char *)s;
    for (unsigned i = 0; i < sizeof(fd_set); i++) p[i] = 0;
}
static inline unsigned U_ps3_fd_words(void)
{
    return sizeof(fd_set) / sizeof(unsigned);
}
static inline void U_ps3_fd_set(int fd, fd_set *s)
{
    unsigned raw = (unsigned)fd & ~(unsigned)SOCKET_FD_MASK;
    if (raw / 32u < U_ps3_fd_words())
        ((unsigned *)s)[raw / 32u] |= (1u << (raw % 32u));
}
static inline void U_ps3_fd_clr(int fd, fd_set *s)
{
    unsigned raw = (unsigned)fd & ~(unsigned)SOCKET_FD_MASK;
    if (raw / 32u < U_ps3_fd_words())
        ((unsigned *)s)[raw / 32u] &= ~(1u << (raw % 32u));
}
static inline int U_ps3_fd_isset(int fd, const fd_set *s)
{
    unsigned raw = (unsigned)fd & ~(unsigned)SOCKET_FD_MASK;
    if (raw / 32u >= U_ps3_fd_words()) return 0;
    return ((((const unsigned *)s)[raw / 32u] >> (raw % 32u)) & 1u) != 0;
}
#define FD_ZERO(s) U_ps3_fd_zero(s)
#define FD_SET(f, s) U_ps3_fd_set((f), (s))
#define FD_CLR(f, s) U_ps3_fd_clr((f), (s))
#define FD_ISSET(f, s) U_ps3_fd_isset((f), (s))

static inline void U_wrapperStart() {
    netInitialize();
};

static inline void U_wrapperEnd() {
    netDeinitialize();
};

static inline void U_sleep(int msec) {
    sysUsleep(msec * 1000); // Syscall 141 receives microseconds, so multiply by 1000 to convert milliseconds to microseconds
};

static inline uint64_t U_millis() {
    u64 sec, nsec;
    sysGetCurrentTime(&sec, &nsec);
    return (sec * 1000) + (nsec / 1000000);
};

/* Networking functions */

static inline int U_socket(int domain, int type, int protocol) {
    return socket(domain, type, protocol);
};

static inline int U_setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen) {
    return setsockopt(sockfd, level, optname, optval, optlen);
};

static inline int U_setsocknonblock(int sockfd){
    int opt = 1;
    return setsockopt(sockfd, SOL_SOCKET, SO_NBIO, &opt, sizeof(opt)); // Use SO_NBIO to set non-blocking mode on PS3
};

static inline int U_bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    return bind(sockfd, addr, addrlen);
};

static inline int U_listen(int sockfd, int backlog) {
    return listen(sockfd, backlog);
};

static inline int U_select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout) {
    return select(nfds, readfds, writefds, exceptfds, timeout);
};

static inline int U_accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {
    return accept(sockfd, addr, addrlen);
};

static inline int U_getpeername(int sockfd, struct sockaddr *addr, socklen_t *addrlen){
    return getpeername(sockfd, addr, addrlen);
};

static inline struct hostent *U_gethostbyname(const char *name) {
    return gethostbyname(name);
};

static inline char *U_inet_ntoa(struct in_addr in){
    return inet_ntoa(in);
};

static inline ssize_t U_recv(int sockfd, void *buf, size_t len, int flags){
    return recv(sockfd, buf, len, flags);
};

static inline ssize_t U_send(int sockfd, const void *buf, size_t len, int flags){
    return send(sockfd, buf, len, flags);
};

static inline int U_connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    return connect(sockfd, addr, addrlen);
};

static inline int U_close(int fd) {
    return close(fd);
};

static inline int U_shutdown(int sockfd, int how) {
    return shutdown(sockfd, how);
};

/* Memory functions */

static inline void *U_malloc(size_t size) {
    return malloc(size);
};

static inline void *U_calloc(size_t nmemb, size_t size) {
    return calloc(nmemb, size);
};

static inline void *U_realloc(void *ptr, size_t size) {
    return realloc(ptr, size);
};

static inline void U_free(void *ptr) {
    free(ptr);
};

#endif
