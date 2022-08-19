#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "FreeRTOS.h"
#include "task.h"

void turn_led_on(__unused void *params) {
    while (true) {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1); 
        vTaskDelay(250 / portTICK_PERIOD_MS);
    }
}

void turn_led_off(__unused void *params) {
    while (true) {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0); 
        vTaskDelay(612 / portTICK_PERIOD_MS);
    }
}

int main() {
    stdio_init_all();
    
    if (cyw43_arch_init()) {
        printf("WiFi init failed");
        return -1;
    }
    
    TaskHandle_t handleOn = NULL;
    TaskHandle_t handleOff = NULL;
    
    xTaskCreate(turn_led_on, "ledon", 256, NULL, tskIDLE_PRIORITY + 1, &handleOn);
    xTaskCreate(turn_led_off, "ledoff", 256, NULL, tskIDLE_PRIORITY + 1, &handleOff);
    
    vTaskStartScheduler();
    
    while (true) {}
}
