/**
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"

#include "lwip/ip4_addr.h"

#include "FreeRTOS.h"
#include "task.h"
#include "ping.h"

#ifndef PING_ADDR
#define PING_ADDR "142.251.35.196"
#endif
#ifndef RUN_FREERTOS_ON_CORE
#define RUN_FREERTOS_ON_CORE 0
#endif

#define TEST_TASK_PRIORITY				( tskIDLE_PRIORITY + 1UL )

void run_ping_test(__unused void *params) {
    if (cyw43_arch_init()) {
        printf("failed to initialise\n");
        return;
    }
    cyw43_arch_enable_sta_mode();
    printf("Connecting to WiFi...\n");
    if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 30000)) {
        printf("failed to connect.\n");
        exit(1);
    }
    else {
        printf("Connected.\n");
    }

    ip_addr_t ping_addr;
    ip4_addr_set_u32(&ping_addr, ipaddr_addr(PING_ADDR));
    ping_init(&ping_addr);

    while (true) {
        // not much to do as LED is in another task, and we're using RAW (callback) lwIP API
        vTaskDelay(100);
    }

    cyw43_arch_deinit();
}

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

void vLaunch(void) {
    TaskHandle_t testTask;
    xTaskCreate(run_ping_test, "TestMainThread", 512, NULL, TEST_TASK_PRIORITY, &testTask);

    TaskHandle_t handleOn = NULL;
    TaskHandle_t handleOff = NULL;
    
    xTaskCreate(turn_led_on, "ledon", 512, NULL, tskIDLE_PRIORITY + 1, &handleOn);
    xTaskCreate(turn_led_off, "ledoff", 512, NULL, tskIDLE_PRIORITY + 1, &handleOff);
    
    vTaskStartScheduler();
}

int main(void) {
    stdio_init_all();

    vLaunch();

    return 0;
}
