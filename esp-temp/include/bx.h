#pragma once

extern QueueHandle_t bx_queue;
extern SemaphoreHandle_t bx_semaphore;

void IRAM_ATTR onBxPress();

void bx_init();

void button_task(void* parameter);