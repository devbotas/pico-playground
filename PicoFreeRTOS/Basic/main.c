#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

int main() {
    stdio_init_all();
    
    while (true) {
        printf("Sveiks, Girdauskai!\n");
        sleep_ms(1000);
    }
}