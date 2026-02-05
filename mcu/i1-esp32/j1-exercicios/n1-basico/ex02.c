#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

/* funções */
void base();
void ease();
void medium();
void hard();

#define LED_PIN GPIO_NUM_2 // Led interno
#define BUTTON_PIN GPIO_NUM_0  // Boot button

// com esse delay o led fica piscando quando eu aperto o botão
void base(void)
{
    // LED como saída
    gpio_reset_pin(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    
    // Botão como entrada com pull-up
    gpio_reset_pin(BUTTON_PIN);
    gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BUTTON_PIN, GPIO_PULLUP_ONLY);
    
    while(1) {
        int button_state = gpio_get_level(BUTTON_PIN);
        
        if(button_state == 0) {  // Botão pressionado (pull-up)
            gpio_set_level(LED_PIN, 1);
        } else {
            gpio_set_level(LED_PIN, 0);
        }
        
        vTaskDelay(10 / portTICK_PERIOD_MS);  // Pequeno delay
    }
}

/* inverter lógica */
// ele não desliga completamente apenas diminui a intensidade quando eu aperto o botão
void ease(){
    gpio_reset_pin(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

    gpio_reset_pin(BUTTON_PIN);
    gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BUTTON_PIN, GPIO_PULLUP_ONLY);

    while(1) {
        int button_state = gpio_get_level(BUTTON_PIN);

        if(button_state == 0) {
            gpio_set_level(LED_PIN, 0);
        } else {
            gpio_set_level(LED_PIN, 1);
        }

        vTaskDelay(10 / portTICK_PERIOD_MS);

    }
}

/* toggle led */
//melhor fazer uma mini máquina de estados aqui
void medium(){
    gpio_reset_pin(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

    gpio_reset_pin(BUTTON_PIN);
    gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BUTTON_PIN, GPIO_PULLUP_ONLY);

    bool is_clicked = false;
    bool led_state = false;
    int cnt=0;

    while(1){
        int button_state = gpio_get_level(BUTTON_PIN);
        
        if(button_state == 0) {
            if(is_clicked){
                led_state = !led_state;
                gpio_set_level(LED_PIN, led_state);
                cnt=0;
            }
            is_clicked = false;
        } else if(cnt <= 10'000){
            is_clicked = true;
            cnt++;
        } else {
            gpio_set_level(LED_PIN, led_state);
        }

    }

}

/* contar quantas vezes o botão foi pressionado e mostrar no serial */
void hard(){}