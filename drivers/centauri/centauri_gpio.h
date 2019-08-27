#ifndef CENTAURI_GPIO_H
#define CENTAURI_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

void cent_gpio_set_output_mode(int pin);

void cent_gpio_clear_output_mode(int pin);

void cent_gpio_set_data(int pin);

void cent_gpio_clear_data(int pin);

uint32_t cent_gpio_get_data(int pin);

#ifdef __cplusplus
}
#endif

#endif /* CENTAURI_GPIO_H */
