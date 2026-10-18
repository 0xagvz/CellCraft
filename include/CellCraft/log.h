#ifndef _LOG_H
#define _LOG_H
#include "config.h"

#define LOG_ERROR "ERROR"
#define LOG_INFO "INFO"
#define LOG_WARN "WARN"

#define LOG_RECENT_LINES 13
#define LOG_LINE_SIZE (LOG_BUFFER_SIZE + 32)

void printl(const char *type, const char *fmt, ...);
int log_recent_count(void);
const char *log_recent_line(int index);
#endif