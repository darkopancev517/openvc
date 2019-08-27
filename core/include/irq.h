#ifndef IRQ_H
#define IRQ_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

unsigned irq_disable(void);

unsigned irq_enable(void);

void irq_restore(unsigned state);

int irq_is_in(void);

int irq_is_enable(void);

#ifdef __cplusplus
}
#endif

#endif /* IRQ_H */
