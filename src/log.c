#include "log.h"
#include "config.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#if defined(__PPU__) || defined(__PS3__)
#include <sys/tty.h>
#endif

static char log_ring[LOG_RECENT_LINES][LOG_LINE_SIZE];
static int log_head = 0;
static int log_count = 0;

void printl(const char *type, const char *fmt, ...)
{
    char msg[LOG_BUFFER_SIZE];
    char line[LOG_LINE_SIZE];
    va_list args;
    va_start(args, fmt);
    vsnprintf(msg, sizeof(msg), fmt, args);
    va_end(args);
    snprintf(line, sizeof(line), "[%s]: %s", type, msg);

    snprintf(log_ring[log_head], LOG_LINE_SIZE, "%s", line);
    log_head = (log_head + 1) % LOG_RECENT_LINES;
    if (log_count < LOG_RECENT_LINES)
        log_count++;

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

int log_recent_count(void)
{
    return log_count;
}

const char *log_recent_line(int index)
{
    int start;

    if (index < 0 || index >= log_count)
        return "";

    start = (log_head - log_count + LOG_RECENT_LINES) % LOG_RECENT_LINES;
    return log_ring[(start + index) % LOG_RECENT_LINES];
}
