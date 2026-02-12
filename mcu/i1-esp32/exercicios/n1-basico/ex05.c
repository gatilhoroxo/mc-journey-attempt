#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/* funções para Sons*/

/*código disponibilizado*/
void base();
/* Tocar melodia simples (parabens pra voce) */
void ease();
/* adicionar pausas entre notas e controlar ritmo */
void medium();
/* criar sistema de alarme com padroes de beep diferentes */
void hard();


/* ====================== IMPLEMENTAÇÃO ====================== */

#define BUZZER_PIN GPIO_NUM_4
#define PWM_CHANNEL LEDC_CHANNEL_0

// Frequências das notas (Hz)
#define NOTE_C4 262
#define NOTE_D4 294
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_G4 392
#define NOTE_A4 440
#define NOTE_B4 494
#define NOTE_C5 523

void play_note(int frequency, int duration_ms)
{
    if(frequency > 0) {
        ledc_set_freq(LEDC_LOW_SPEED_MODE, PWM_TIMER, frequency);
        ledc_set_duty(LEDC_LOW_SPEED_MODE, PWM_CHANNEL, 128);  // 50%
        ledc_update_duty(LEDC_LOW_SPEED_MODE, PWM_CHANNEL);
    }
    
    vTaskDelay(duration_ms / portTICK_PERIOD_MS);
    
    // Silêncio
    ledc_set_duty(LEDC_LOW_SPEED_MODE, PWM_CHANNEL, 0);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, PWM_CHANNEL);
    vTaskDelay(50 / portTICK_PERIOD_MS);
}

void base()
{
    // Setup PWM igual ao exercício anterior
    setup_pwm();
    
    while(1) {
        // Toca escala C maior
        play_note(NOTE_C4, 500);
        play_note(NOTE_D4, 500);
        play_note(NOTE_E4, 500);
        play_note(NOTE_F4, 500);
        play_note(NOTE_G4, 500);
        play_note(NOTE_A4, 500);
        play_note(NOTE_B4, 500);
        play_note(NOTE_C5, 500);
        
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}


/* ====================== DESAFIOS ====================== */

void ease(){}

void medium(){}

void hard(){}

