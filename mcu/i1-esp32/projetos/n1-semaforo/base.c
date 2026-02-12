#include "driver/gpio.h"
#include "driver/ledc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

typedef enum {
    STATE_GREEN,
    STATE_YELLOW,
    STATE_RED,
    STATE_PEDESTRIAN_WAIT
} traffic_state_t;

typedef struct {
    traffic_state_t current_state;
    int time_remaining;
    bool pedestrian_requested;
} traffic_system_t;

void setup_leds(void) {
    gpio_reset_pin(LED_RED);
    gpio_reset_pin(LED_YELLOW);
    gpio_reset_pin(LED_GREEN);
    gpio_set_direction(LED_RED, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_YELLOW, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_GREEN, GPIO_MODE_OUTPUT);
}

void setup_button(void) {
    gpio_reset_pin(BTN_PEDESTRIAN);
    gpio_set_direction(BTN_PEDESTRIAN, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BTN_PEDESTRIAN, GPIO_PULLUP_ONLY);
}

void setup_display(void) {
    // Configurar pinos do display 7seg
    // (implementar baseado no Exercício 8)
}

void setup_buzzer(void) {
    // Configurar PWM para buzzer
    // (implementar baseado no Exercício 5)
}

void set_traffic_light(traffic_state_t state) {
    // Apagar todos os LEDs
    gpio_set_level(LED_RED, 0);
    gpio_set_level(LED_YELLOW, 0);
    gpio_set_level(LED_GREEN, 0);
    
    // Acender LED correspondente
    switch(state) {
        case STATE_GREEN:
            gpio_set_level(LED_GREEN, 1);
            break;
        case STATE_YELLOW:
            gpio_set_level(LED_YELLOW, 1);
            break;
        case STATE_RED:
            gpio_set_level(LED_RED, 1);
            break;
    }
}

void play_beep(void) {
    // Tocar beep curto (implementar com buzzer)
}

void display_number(int num) {
    // Exibir número no display (implementar baseado no Exercício 8)
}

bool read_pedestrian_button(void) {
    // Implementar leitura com debounce (Exercício 3)
    static int last_state = 1;
    static uint32_t last_time = 0;
    // ... código de debounce aqui
    return false;
}

void traffic_light_task(void *pvParameters) {
    traffic_system_t system = {
        .current_state = STATE_GREEN,
        .time_remaining = 10,
        .pedestrian_requested = false
    };
    
    while(1) {
        // Verificar botão pedestre
        if(read_pedestrian_button() && gpio_get_level(BTN_PEDESTRIAN) == 0) {
            system.pedestrian_requested = true;
        }
        
        // Exibir tempo no display
        display_number(system.time_remaining);
        
        // Lógica da máquina de estados
        switch(system.current_state) {
            case STATE_GREEN:
                set_traffic_light(STATE_GREEN);
                
                // Piscar LED verde nos últimos 3 segundos
                if(system.time_remaining <= 3) {
                    gpio_set_level(LED_GREEN, system.time_remaining % 2);
                }
                
                if(system.time_remaining <= 0) {
                    system.current_state = STATE_YELLOW;
                    system.time_remaining = 3;
                    play_beep();
                }
                break;
                
            case STATE_YELLOW:
                set_traffic_light(STATE_YELLOW);
                
                if(system.time_remaining <= 0) {
                    system.current_state = STATE_RED;
                    system.time_remaining = 10;
                    play_beep();
                }
                break;
                
            case STATE_RED:
                set_traffic_light(STATE_RED);
                
                // Se pedestre solicitou, dar mais tempo
                if(system.pedestrian_requested && system.time_remaining > 5) {
                    system.time_remaining = 15;  // Extende tempo vermelho
                    system.pedestrian_requested = false;
                }
                
                if(system.time_remaining <= 0) {
                    system.current_state = STATE_GREEN;
                    system.time_remaining = 10;
                    play_beep();
                }
                break;
        }
        
        system.time_remaining--;
        vTaskDelay(1000 / portTICK_PERIOD_MS);  // 1 segundo
    }
}

void app_main(void) {
    setup_leds();
    setup_button();
    setup_display();
    setup_buzzer();
    
    xTaskCreate(traffic_light_task, "traffic_light", 4096, NULL, 5, NULL);
}
