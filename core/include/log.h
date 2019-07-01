#ifndef LOG_H
#define LOG_H

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

enum {
    LOG_NONE,
    LOG_ERROR,
    LOG_WARNING,
    LOG_INFO,
    LOG_DEBUG,
    LOG_ALL
};

#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_INFO
#endif

#define LOG(level, ...) do { \
    if ((level) <= LOG_LEVEL) log_write((level), __VA_ARGS__); } while (0U)

#define LOG_ERROR(...) LOG(LOG_ERROR, __VA_ARGS__)
#define LOG_WARNING(...) LOG(LOG_WARNING, __VA_ARGS__)
#define LOG_INFO(...) LOG(LOG_INFO, __VA_ARGS__)
#define LOG_DEBUG(...) LOG(LOG_DEBUG, __VA_ARGS__)

#define log_write(level, ...) printf(__VA_ARGS__);

#ifdef __cplusplus
}
#endif

#endif /* LOG_H */
