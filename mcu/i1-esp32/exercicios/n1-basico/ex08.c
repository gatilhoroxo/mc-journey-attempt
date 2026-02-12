#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/* funções para Display 7 segmentos */

/*código disponibilizado*/
void base();
/* mostrar os dígitos ao pressionar um botao, incrementa a cada clique */
void ease();
/* contar de 0 a 9 e depois de 9 para 0, alternando */
void medium();
/* exibir um contador controlado por dois botoes: um incrementa e outro decrementa */
void hard();


/* ====================== IMPLEMENTAÇÃO ====================== */

// Definir pinos (ajuste conforme sua conexão)
#define SEG_A GPIO_NUM_13
#define SEG_B GPIO_NUM_12
#define SEG_C GPIO_NUM_14
#define SEG_D GPIO_NUM_27
#define SEG_E GPIO_NUM_26
#define SEG_F GPIO_NUM_25
#define SEG_G GPIO_NUM_33

const gpio_num_t segments[] = {SEG_A, SEG_B, SEG_C, SEG_D, SEG_E, SEG_F, SEG_G};

// Padrões para dígitos 0-9 (catodo comum)
const uint8_t digit_patterns[] = {
    0b00111111,  // 0
    0b00000110,  // 1
    0b01011011,  // 2
    0b01001111,  // 3
    0b01100110,  // 4
    0b01101101,  // 5
    0b01111101,  // 6
    0b00000111,  // 7
    0b01111111,  // 8
    0b01101111   // 9
};

void setup_7seg(void)
{
    for(int i = 0; i < 7; i++) {
        gpio_reset_pin(segments[i]);
        gpio_set_direction(segments[i], GPIO_MODE_OUTPUT);
    }
}

void display_digit(int digit)
{
    if(digit < 0 || digit > 9) return;
    
    uint8_t pattern = digit_patterns[digit];
    
    for(int i = 0; i < 7; i++) {
        gpio_set_level(segments[i], (pattern >> i) & 1);
    }
}


void base()
{
    setup_7seg();
    
    int counter = 0;
    
    while(1) {
        display_digit(counter);
        counter = (counter + 1) % 10;
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}



/* ====================== DESAFIOS ====================== */

void ease(){}

void medium(){}

void hard(){}

