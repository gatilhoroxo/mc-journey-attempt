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

/* inverter lógica */
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

/* toggle led */
//melhor fazer uma mini máquina de estados aqui
void medium(){
    gpio_reset_pin(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

    gpio_reset_pin(BUTTON_PIN);
    gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BUTTON_PIN, GPIO_PULLUP_ONLY);

    typedef enum {
        apertado, solto
    } states;

    states botao = solto;
    states aux = solto;
    int led_state = false;
    int cnt=0;


    while(1){
        int button_state = gpio_get_level(BUTTON_PIN);
        
        /*máquina de estados para lidar com os estados do botao*/
        // TO-DO: testar com outro botão sem ser o do boot
        bool regra = cnt >= 50'000 && cnt <= 60'000;
        if(button_state == 0 && aux == apertado && regra){
            botao = apertado;
            cnt=0;
        } else if(button_state == 0) {
            aux = solto;
            botao = solto;
        } else if(cnt < 50'000){
            cnt++;
        } else if(regra){
            aux = apertado;
        } 

        /*máquina de estados para lidar com os estados do led*/
        switch (botao)
        {
        case apertado:
            led_state = !led_state;
            break;
        default:
            led_state = led_state;
            break;
        }

        gpio_set_level(LED_PIN, led_state);

    }

}

/* contar quantas vezes o botão foi pressionado e mostrar no serial */
void hard(){}