#include "log.h"
#include "config.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#if defined(__PPU__) || defined(__PS3__)
#include <sys/tty.h>
#endif

void printl(const char *type, const char *fmt, ...)
{
    char msg[LOG_BUFFER_SIZE];
    char line[LOG_BUFFER_SIZE + 32];
    va_list args;
    va_start(args, fmt);
    vsnprintf(msg, sizeof(msg), fmt, args);
    va_end(args);
    snprintf(line, sizeof(line), "[%s]: %s", type, msg);
#if defined(__PPU__) || defined(__PS3__)
    {
        u32 written = 0;
        sysTtyWrite(0, line, strlen(line), &written);
    }
#else
    printf("%s", line);
    fflush(stdout);
#endif
}
