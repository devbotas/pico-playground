#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "FreeRTOS.h"
#include <task.h>

// Set a delay time of exactly 500ms
const TickType_t ms_delay = 500 / portTICK_PERIOD_MS;

// FROM 1.0.1 Record references to the tasks
TaskHandle_t gpio_task_handle = NULL;
TaskHandle_t pico_task_handle = NULL;

void led_task_pico(void* unused_arg);
void led_task_gpio(void* unused_arg);

int main() {
    stdio_init_all();
    printf("papai");
    if (cyw43_arch_init()) {
        printf("WiFi init failed");
        return -1;
    }
    
    BaseType_t pico_status = xTaskCreate(led_task_pico, "PICO_LED_TASK", 128, NULL, 1, &pico_task_handle);
    BaseType_t gpio_status = xTaskCreate(led_task_gpio, "GPIO_LED_TASK", 128, NULL, 1, &gpio_task_handle);
    
    if (pico_status == pdPASS || gpio_status == pdPASS) {
        vTaskStartScheduler();
    }
    
    while (true) {
        printf("bybis");
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        sleep_ms(250);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        sleep_ms(1250);
    }
}

void led_task_pico(void* unused_arg) {

    while (true) {
        printf("bybis");
        //cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        vTaskDelay(ms_delay);
    }
}
void led_task_gpio(void* unused_arg) {
   
    while (true) {
        printf("pyzda");
        //cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        vTaskDelay(ms_delay * 2);
    }
}