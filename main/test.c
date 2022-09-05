#include "driver/touch_pad.h"
#include <stdlib.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include <stdio.h>
#include <string.h>
#include "driver/gpio.h"

static QueueHandle_t gpio_evt_queue = NULL;

static void IRAM_ATTR gpio_isr_handler(void* arg)
{
    uint32_t gpio_num = (uint32_t) arg;
    xQueueSendFromISR(gpio_evt_queue, &gpio_num, NULL);
}

void app_main(void){
    touch_pad_init();
    touch_pad_set_voltage(TOUCH_HVOLT_2V4, TOUCH_LVOLT_0V5, TOUCH_HVOLT_ATTEN_1V);
    touch_pad_config(TOUCH_PAD_NUM4, 0);
    uint16_t output;
    touch_pad_read(TOUCH_PAD_NUM4,&output);

//    gpio_config_t gpio25;
//    gpio25.pin_bit_mask = 25;
//    gpio25.mode = GPIO_MODE_OUTPUT;
//    gpio_config(&gpio25);
//    gpio_reset_pin(25);
//    gpio_set_direction(25, GPIO_MODE_OUTPUT);
//    gpio_set_level(25, 1);

    while (1){
        touch_pad_read(TOUCH_PAD_NUM4,&output);
        printf("%d\n", output);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}