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
#define TEST_TASK_PRIORITY				( tskIDLE_PRIORITY + 1UL )

void main_task(__unused void *params) {
    if (cyw43_arch_init()) {
        printf("failed to initialise\n");
        return;
    }
    cyw43_arch_enable_sta_mode();
    printf("Connecting to WiFi...\n");
    printf(WIFI_PASSWORD);
    //if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 30000)) {
    cyw43_arch_wifi_connect_async(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_MIXED_PSK);
    //        printf("failed to connect.\n");
    //        //exit(1);
    //    }
    //    else {
    //        printf("Connected.\n");
    //    }

        // ip_addr_t ping_addr;
        // ip4_addr_set_u32(&ping_addr, ipaddr_addr(PING_ADDR));
        // ping_init(&ping_addr);

    while (true) {
        int bybis = cyw43_wifi_link_status(&cyw43_state, CYW43_ITF_STA);
        printf("%i", bybis);
        // not much to do as LED is in another task, and we're using RAW (callback) lwIP API
        vTaskDelay(1000);
    }

    cyw43_arch_deinit();
}

void vLaunch(void) {
    TaskHandle_t task;
    xTaskCreate(main_task, "TestMainThread", configMINIMAL_STACK_SIZE, NULL, TEST_TASK_PRIORITY, &task);

     
    BaseType_t pico_status = xTaskCreate(led_task_pico, "PICO_LED_TASK", configMINIMAL_STACK_SIZE, NULL, 1, &pico_task_handle);
    BaseType_t gpio_status = xTaskCreate(led_task_gpio, "GPIO_LED_TASK", configMINIMAL_STACK_SIZE, NULL, 1, &gpio_task_handle);
    
#if NO_SYS && configUSE_CORE_AFFINITY && configNUM_CORES > 1
    // we must bind the main task to one core (well at least while the init is called)
    // (note we only do this in NO_SYS mode, because cyw43_arch_freertos
    // takes care of it otherwise)
    vTaskCoreAffinitySet(task, 1);
#endif

    /* Start the tasks and timer running. */
    vTaskStartScheduler();
}

int main() {
    stdio_init_all();
    /* Configure the hardware ready to run the demo. */
    const char *rtos_name;
#if ( portSUPPORT_SMP == 1 )
    rtos_name = "FreeRTOS SMP";
#else
    rtos_name = "FreeRTOS";
#endif

#if ( portSUPPORT_SMP == 1 ) && ( configNUM_CORES == 2 )
    printf("Starting %s on both cores:\n", rtos_name);
    vLaunch();
#elif ( RUN_FREE_RTOS_ON_CORE == 1 )
    printf("Starting %s on core 1:\n", rtos_name);
    multicore_launch_core1(vLaunch);
    while (true) ;
#else
    printf("Starting %s on core 0:\n", rtos_name);
    vLaunch();
#endif
    return 0;
    
    //    
    //   
    //    printf("papai");
    //    if (cyw43_arch_init()) {
    //        printf("WiFi init failed");
    //        return -1;
    //    }
    //    
    //    BaseType_t pico_status = xTaskCreate(led_task_pico, "PICO_LED_TASK", 128, NULL, 1, &pico_task_handle);
    //    BaseType_t gpio_status = xTaskCreate(led_task_gpio, "GPIO_LED_TASK", 128, NULL, 1, &gpio_task_handle);
    //    
    //    if (pico_status == pdPASS || gpio_status == pdPASS) {
    //        vTaskStartScheduler();
    //    }
    //    
    //    while (true) {
    //        //        printf("bybis");
    //        //        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    //        //        sleep_ms(250);
    //        //        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    //        //        sleep_ms(1250);
    //    }
}

void led_task_pico(void* unused_arg) {

    while (true) {
        printf("subine");
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        vTaskDelay(ms_delay);
    }
}
void led_task_gpio(void* unused_arg) {
   
    while (true) {
        printf("pyzda");
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        vTaskDelay(ms_delay * 2);
    }
}

