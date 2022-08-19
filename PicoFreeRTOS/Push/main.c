#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

void handle_gpio_callback(uint gpio, uint32_t events) {
    if ((events & 0x1) == 0x1) {
        printf("GPIO %d level low.\n", gpio);
    }
    if ((events & 0x2) == 0x2) {
        printf("GPIO %d level high. \n", gpio);
    }
    if ((events & 0x4) == 0x4) {
        printf("GPIO %d edge fall.\n", gpio);
    }
    if ((events & 0x8) == 0x8) {
        printf("GPIO %d edge rise.\n", gpio);
    }
}

int main() {
    stdio_init_all();

    printf("Hello GPIO IRQ\n");
    
    gpio_pull_up(12);
    gpio_pull_up(13);
    gpio_set_irq_enabled_with_callback(12, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &handle_gpio_callback);
    gpio_set_irq_enabled_with_callback(13, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &handle_gpio_callback);

    while (1) ;
}
