#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

/* funções para GPIO Basico*/

/*código disponibilizado*/
void base();
/* inverter lógica */
void ease();
/* toggle led - ligar led quando apertado o botao, desligar led quando o aperta de novo */
void medium();
/* contar quantas vezes o botão foi pressionado e mostrar no serial */
void hard();

/* ====================== IMPLEMENTAÇÃO ====================== */

#define LED_PIN GPIO_NUM_8 
#define BUTTON_PIN GPIO_NUM_4  

// com esse delay o led fica piscando quando eu aperto o botão
/*Motivo: o botão de boot da esp32 não é um botão limpo e ele pode gerar ruído quando é pressionado e com esse delay para ler o estado do botão ele pode detectar múltiplas transações rápidas enquanto o botão está sendo pressionado, ou seja, ele fica "piscando".*/
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


/* ====================== DESAFIOS ====================== */

// ele não desliga completamente apenas diminui a intensidade quando eu aperto o botão
/*Motivo: o led interno da esp32 é ligado ao gpio2 que pode ter outros circuitos conectados internamente, o que pode acabar deixando uma corrente residual e não fazendo ele apagar por completo.*/
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


//a maquina de estados nao funciona direito aqui
//tentei varias vezes e ainda nao esta funcionando
void medium(){
    gpio_reset_pin(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

    gpio_reset_pin(BUTTON_PIN);
    gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BUTTON_PIN, GPIO_PULLUP_ONLY);

    typedef enum {
        apertado, solto
    } states;

    states bnt_atual = solto;
    states bnt_ant = solto;
    int led_state = false;

    while(1){
        int button_state = gpio_get_level(BUTTON_PIN);
        if(button_state == 0) bnt_atual = apertado;
        else bnt_atual = solto;

        states bnt_aux = solto;
        if(bnt_atual != bnt_ant) {
            bnt_aux = bnt_atual;
            vTaskDelay(100 / portTICK_PERIOD_MS);
        }

        button_state = gpio_get_level(BUTTON_PIN);
        if(button_state == 0) bnt_atual = apertado;
        else bnt_atual = solto;

        if(bnt_atual == bnt_aux && bnt_atual != bnt_ant) {
            if(bnt_ant == solto && bnt_atual == apertado){
                led_state = !led_state;
            }
            bnt_ant = bnt_atual;
        }

        gpio_set_level(LED_PIN, led_state);
        vTaskDelay(20 / portTICK_PERIOD_MS);
    }

}

//
void hard(){}