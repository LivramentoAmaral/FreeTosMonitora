#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

// Define o pino para o LED
const uint32_t LED_PIN = 12;

// Define o pino para o botão
#define BUTTON_PIN 6

// Define as variáveis para armazenar o estado do botão
volatile int buttonState = 0;

// Tarefa para ler o estado do botão e atualizar a variável buttonState
void ButtonTask(void *pvParameters) {
    for (;;) {
        if (!gpio_get(BUTTON_PIN)) {
            buttonState = 1; // Botão pressionado
            printf("Botão pressionado\n"); // Imprimir estado do botão
        } else {
            buttonState = 0; // Botão não pressionado
            printf("Botão não pressionado\n"); // Imprimir estado do botão
        }
        vTaskDelay(pdMS_TO_TICKS(100)); // Atraso para debouncing
    }
}

// Tarefa para controlar o LED com base nas notificações
void LedTask(void *pvParameters) {
    for (;;) {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY); // Esperar pela notificação
        printf("LED LIGADO\n"); // Imprimir mudança no estado do LED
        gpio_put(LED_PIN, 1); // Ligar o LED
        vTaskDelay(pdMS_TO_TICKS(100)); // Esperar 100ms
        printf("LED DESLIGADO\n"); // Imprimir mudança no estado do LED
        gpio_put(LED_PIN, 0); // Desligar o LED
        vTaskDelay(pdMS_TO_TICKS(100)); // Esperar 100ms
    }
}

// Tarefa para processar o estado do botão e notificar a tarefa do LED
void ProcessTask(void *pvParameters) {
    TaskHandle_t *ledTaskHandle = (TaskHandle_t *)pvParameters;
    for (;;) {
        if (buttonState == 1) {
            printf("Botão pressionado, notificando tarefa do LED\n"); // Imprimir evento de notificação
            xTaskNotifyGive(*ledTaskHandle); // Notificar a tarefa do LED para ligar o LED
        }
        vTaskDelay(pdMS_TO_TICKS(100)); // Verificar a cada 100ms
    }
}

// Função principal
int main(void) {
    TaskHandle_t ledTaskHandle = NULL;

    // Inicializar entrada/saída padrão para depuração
    stdio_init_all();

    // Inicializar o pino do LED
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    // Inicializar o pino do botão com resistor de pull-up
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    // Criar as tarefas do FreeRTOS
    xTaskCreate(ButtonTask, "Tarefa do Botão", 128, NULL, 2, NULL);
    xTaskCreate(LedTask, "Tarefa do LED", 128, NULL, 1, &ledTaskHandle);
    xTaskCreate(ProcessTask, "Tarefa de Processamento", 128, (void*)&ledTaskHandle, 1, NULL);

    // Iniciar o escalonador do FreeRTOS
    vTaskStartScheduler();

    // Retornar 0 (Este ponto nunca deve ser alcançado)
    return 0;
}
