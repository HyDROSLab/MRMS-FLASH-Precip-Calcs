#ifndef MESSAGES_H
#define MESSAGES_H

#ifndef _WIN32
#define LOGFR(...) printf(__VA_ARGS__)
#define NORMAL_LOGF(x, ...) printf(x, __VA_ARGS__)
#define DEBUG_LOGF(x, ...) LOGFR("DEBUG:" __FILE__ "(%i): " x "\n", __LINE__, __VA_ARGS__)
#define INFO_LOGF(x, ...) LOGFR("INFO:" __FILE__ "(%i): " x "\n", __LINE__, __VA_ARGS__)
#define WARNING_LOGF(x, ...) LOGFR("WARNING:" __FILE__ "(%i): " x "\n", __LINE__, __VA_ARGS__)
#define ERROR_LOG(x) LOGFR("ERROR:" __FILE__ "(%i): " x "\n", __LINE__)
#define ERROR_LOGF(x, ...) LOGFR("ERROR:" __FILE__ "(%i): " x "\n", __LINE__, __VA_ARGS__)
#else
#include "EF5Windows.h"
#define NORMAL_LOGF(x, ...) addConsoleText(NORMAL, x, __VA_ARGS__)
#define DEBUG_LOGF(x, ...) addConsoleText(INFOFMATION, x, __VA_ARGS__)
#define INFO_LOGF(x, ...) addConsoleText(INFORMATION, x, __VA_ARGS__)
#define WARNING_LOGF(x, ...) addConsoleText(WARNING, x, __VA_ARGS__)
#define ERROR_LOG(x) addConsoleText(FATAL, "%s", x)
#define ERROR_LOGF(x, ...) addConsoleText(FATAL, x, __VA_ARGS__)
#endif

#endif
