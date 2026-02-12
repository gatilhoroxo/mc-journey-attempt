#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"
#include "driver/adc.h"

/* funções para ADC */

/*código disponibilizado*/
void base();
/* adicionar histerese para evitar flickering */
void ease();
/* controlar frequência de buzzer com potenciômetro */
void medium();
/* controlar cor de LED RGB usando 3 potenciômetros */
void hard();


/* ====================== IMPLEMENTAÇÃO ====================== */

#define POT_PIN ADC1_CHANNEL_6  // GPIO34

void base()
{
    setup_pwm();
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(POT_PIN, ADC_ATTEN_DB_11);
    
    while(1) {
        int raw = adc1_get_raw(POT_PIN);
        int duty = (raw * 255) / 4095;  // Mapeia 0-4095 para 0-255
        
        ledc_set_duty(LEDC_LOW_SPEED_MODE, PWM_CHANNEL, duty);
        ledc_update_duty(LEDC_LOW_SPEED_MODE, PWM_CHANNEL);
        
        printf("Brilho: %d%%\n", (duty * 100) / 255);
        
        vTaskDelay(50 / portTICK_PERIOD_MS);
    }
}

/* ====================== DESAFIOS ====================== */

void ease(){}

void medium(){}

void hard(){}

