#pragma once

extern QueueHandle_t bx_queue;
extern SemaphoreHandle_t bx_semaphore;

void IRAM_ATTR onBxPress();

void bx_init();

void bx_task(void* parameter);

uint8_t change_data_type(uint8_t data_type);