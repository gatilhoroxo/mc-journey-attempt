#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"

/* funções para PWM*/

/*código disponibilizado*/
void base();
/* inverter animação */
void ease();
/* criar efeito de "respiração" com velocidade variável */
void medium();
/* controlar 3 leds rgb independentemente criando efeitos de cores */
void hard();


/* ====================== IMPLEMENTAÇÃO ====================== */


#define LED_PIN GPIO_NUM_2
#define PWM_CHANNEL LEDC_CHANNEL_0
#define PWM_TIMER LEDC_TIMER_0

void setup_pwm(void)
{
    // Configurar timer
    ledc_timer_config_t timer_conf = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .duty_resolution = LEDC_TIMER_8_BIT,  // 0-255
        .timer_num = PWM_TIMER,
        .freq_hz = 5000,
        .clk_cfg = LEDC_AUTO_CLK
    };
    ledc_timer_config(&timer_conf);
    
    // Configurar canal
    ledc_channel_config_t channel_conf = {
        .gpio_num = LED_PIN,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = PWM_CHANNEL,
        .timer_sel = PWM_TIMER,
        .duty = 0,
        .hpoint = 0
    };
    ledc_channel_config(&channel_conf);
}

void base()
{
    setup_pwm();
    
    while(1) {
        // Fade in
        for(int duty = 0; duty <= 255; duty++) {
            ledc_set_duty(LEDC_LOW_SPEED_MODE, PWM_CHANNEL, duty);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, PWM_CHANNEL);
            vTaskDelay(10 / portTICK_PERIOD_MS);
        }
        
        // Fade out
        for(int duty = 255; duty >= 0; duty--) {
            ledc_set_duty(LEDC_LOW_SPEED_MODE, PWM_CHANNEL, duty);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, PWM_CHANNEL);
            vTaskDelay(10 / portTICK_PERIOD_MS);
        }
    }
}

/* ====================== DESAFIOS ====================== */

void ease(){}

void medium(){}

void hard(){}

