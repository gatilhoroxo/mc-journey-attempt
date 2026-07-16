#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

/* funções para GPIO Basico*/

/*código disponibilizado*/
void base();
/* tempo de debounce para 100ms */
void ease();
/* detecção de pressionamento longo */
void medium();
/* contar cliques duplos (double-click) */
void hard();


/* ====================== IMPLEMENTAÇÃO ====================== */


#define LED_PIN GPIO_NUM_2 // Led interno
#define DEBOUNCE_TIME_MS 50
#define BUTTON_PIN GPIO_NUM_0  // Boot button

bool read_button_debounced(gpio_num_t pin) {
    static int last_state = 1;
    static uint32_t last_time = 0;
    
    int current_state = gpio_get_level(pin);
    uint32_t current_time = xTaskGetTickCount() * portTICK_PERIOD_MS;
    
    if(current_state != last_state) {
        if((current_time - last_time) > DEBOUNCE_TIME_MS) {
            last_state = current_state;
            last_time = current_time;
            return true;  // Mudança válida
        }
    }
    
    return false;
}

void base()
{
    gpio_reset_pin(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    gpio_reset_pin(BUTTON_PIN);
    gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BUTTON_PIN, GPIO_PULLUP_ONLY);
    
    bool led_state = false;
    
    while(1) {portTICK_PERIOD_MS
        if(read_button_debounced(BUTTON_PIN)) {
            if(gpio_get_level(BUTTON_PIN) == 0) {
                led_state = !led_state;
                gpio_set_level(LED_PIN, led_state);
            }
        }
        vTaskDelay(1 / portTICK_PERIOD_MS);
    }
}



/* ====================== DESAFIOS ====================== */

void ease(){}

void medium(){}

void hard(){}

