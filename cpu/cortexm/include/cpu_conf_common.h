#ifndef CPU_CONF_COMMON_H
#define CPU_CONF_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Configuration of default stack sizes
 */
#ifndef THREAD_EXTRA_STACKSIZE_PRINTF
#define THREAD_EXTRA_STACKSIZE_PRINTF   (512)
#endif
#ifndef THREAD_STACKSIZE_DEFAULT
#define THREAD_STACKSIZE_DEFAULT        (1024)
#endif
#ifndef THREAD_STACKSIZE_IDLE
#define THREAD_STACKSIZE_IDLE           (256)
#endif

#ifndef ISR_STACKSIZE
#define ISR_STACKSIZE                   (512U)
#endif

#ifdef __cplusplus
}
#endif

#endif /* CPU_CONF_COMMON_H */
