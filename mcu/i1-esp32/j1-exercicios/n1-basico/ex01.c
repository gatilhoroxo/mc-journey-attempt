#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG = "LED_EXERCISES";

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

typedef struct {
    gpio_num_t led_pin;
    gpio_num_t led_red;
    const char *task_name;
} task_param_ease_t;

typedef struct {
    gpio_num_t led;
    const char *task_name;
} task_param_medium_t;

typedef struct {
    gpio_num_t led_red;
    gpio_num_t led_yellow;
    gpio_num_t led_green;
    const char *task_name;
} task_param_hard_t;

// soluções do exercício 1
void easy(void *pvParameters);
void medium(void *pvParameters);
void hard(void *pvParameters);

void extra(){
    static task_param_ease_t p_ease = {
        .led_pin = GPIO_NUM_2,
        .led_red = GPIO_NUM_25,
        .task_name = "Easy Task"
    };

    static task_param_medium_t p_medium = {
        .led = GPIO_NUM_26,
        .task_name = "Medium Task"
    };

    static task_param_hard_t p_hard = {
        .led_red = GPIO_NUM_13,
        .led_yellow = GPIO_NUM_12,
        .led_green = GPIO_NUM_14,
        .task_name = "Hard Task"
    };

    xTaskCreate(easy, "easy task", 2048, &p_ease, 5, NULL);
    xTaskCreate(medium, "medium task", 2048, &p_medium, 5, NULL);
    xTaskCreate(hard, "hard task", 2048, &p_hard, 5, NULL);

}

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

// Constantes de timing Morse
#define MORSE_DOT_MS 300
#define MORSE_DASH_MS 800
#define MORSE_SYMBOL_GAP_MS 300
#define MORSE_LETTER_GAP_MS 1000

// Estrutura para simplificar controle de múltiplos LEDs
typedef struct {
    gpio_num_t pin;
    uint8_t state;
} led_t;

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void led_init(gpio_num_t gpio);
void led_set(gpio_num_t gpio, uint8_t state);
void led_toggle(gpio_num_t gpio, uint32_t delay_ms);
void leds_set_pattern(led_t leds[3], uint32_t duration_ms);

void morse_pulse(gpio_num_t gpio, uint32_t on_time_ms);
void morse_dot(gpio_num_t gpio);
void morse_dash(gpio_num_t gpio);
void morse_S(gpio_num_t gpio);
void morse_O(gpio_num_t gpio);
void morse_SOS(gpio_num_t gpio);

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
// Exercícios
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void easy(void *pvParameters) {
    ESP_LOGI(TAG, "Iniciando: EASY - Blink alternado");

    task_param_ease_t *p = (task_param_ease_t *)pvParameters;
    
    gpio_num_t led_pin = p->led_pin;
    gpio_num_t led_red = p->led_red;

    led_init(led_pin);
    led_init(led_red);
    
    while (1) {
        led_set(led_pin, 1);
        led_set(led_red, 0);
        vTaskDelay(pdMS_TO_TICKS(300));
        
        led_set(led_pin, 0);
        led_set(led_red, 1);
        vTaskDelay(pdMS_TO_TICKS(300));
    }
}

void medium(void *pvParameters) {
    ESP_LOGI(TAG, "Iniciando: MEDIUM - Morse SOS");
    
    task_param_medium_t *p = (task_param_medium_t *)pvParameters;

    gpio_num_t led_red = p->led;
    
    led_init(led_red);
    
    while (1) {
        morse_SOS(led_red);
        vTaskDelay(pdMS_TO_TICKS(2000)); // Pausa entre repetições
    }
}

void hard(void *pvParameters) {
    ESP_LOGI(TAG, "Iniciando: HARD - Semáforo");

    task_param_hard_t *p = (task_param_hard_t *)pvParameters;

    gpio_num_t led_red = p->led_red;
    gpio_num_t led_yellow = p->led_yellow;
    gpio_num_t led_green = p->led_green;

    led_init(led_red);
    led_init(led_yellow);
    led_init(led_green);

    const uint32_t STATE_DURATION = 1000;

    led_t leds[3] = {{led_red,0}, {led_yellow,0}, {led_green,0}};

    while (1) {
        leds[0].state = 1, leds[1].state = 0, leds[2].state = 0;
        leds_set_pattern(leds, STATE_DURATION);
        leds[0].state = 0, leds[1].state = 1, leds[2].state = 0;
        leds_set_pattern(leds, STATE_DURATION);
        leds[0].state = 0, leds[1].state = 0, leds[2].state = 1;
        leds_set_pattern(leds, STATE_DURATION);

        leds[0].state = 1, leds[1].state = 1, leds[2].state = 1;
        leds_set_pattern(leds, STATE_DURATION);
    }
}

/*&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=*/
/*&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=&=*/

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
// Funções auxiliares
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void led_init(gpio_num_t gpio) {
    gpio_reset_pin(gpio);
    gpio_set_direction(gpio, GPIO_MODE_OUTPUT);
    gpio_set_level(gpio, 0);
}

void led_set(gpio_num_t gpio, uint8_t state) {
    gpio_set_level(gpio, state);
}

void led_toggle(gpio_num_t gpio, uint32_t delay_ms) {
    static uint8_t state = 0;
    state = !state;
    gpio_set_level(gpio, state);
    vTaskDelay(pdMS_TO_TICKS(delay_ms));
}

void leds_set_pattern(led_t leds[3], uint32_t duration_ms) {
    led_set(leds[0].pin, leds[0].state);
    led_set(leds[1].pin, leds[1].state);
    led_set(leds[2].pin, leds[2].state);
    if (duration_ms > 0) {
        vTaskDelay(pdMS_TO_TICKS(duration_ms));
    }
}

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
// Funções Morse otimizadas
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void morse_pulse(gpio_num_t gpio, uint32_t on_time_ms) {
    led_set(gpio, 1);
    vTaskDelay(pdMS_TO_TICKS(on_time_ms));
    led_set(gpio, 0);
    vTaskDelay(pdMS_TO_TICKS(MORSE_SYMBOL_GAP_MS));
}

void morse_dot(gpio_num_t gpio) {
    morse_pulse(gpio, MORSE_DOT_MS);
}

void morse_dash(gpio_num_t gpio) {
    morse_pulse(gpio, MORSE_DASH_MS);
}

void morse_S(gpio_num_t gpio) {
    for (int i = 0; i < 3; i++) {
        morse_dot(gpio);
    }
}

void morse_O(gpio_num_t gpio) {
    for (int i = 0; i < 3; i++) {
        morse_dash(gpio);
    }
}

void morse_SOS(gpio_num_t gpio) {
    morse_S(gpio);
    vTaskDelay(pdMS_TO_TICKS(MORSE_LETTER_GAP_MS));
    morse_O(gpio);
    vTaskDelay(pdMS_TO_TICKS(MORSE_LETTER_GAP_MS));
    morse_S(gpio);
}

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
