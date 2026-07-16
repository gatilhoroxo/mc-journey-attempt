#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"

/* funções para ADC */

/*código disponibilizado*/
void base();
/* exibir valor em percentual */
void ease();
/* criar barágrafo no serial (ex: [====      ] 40%) */
void medium();
/* implementar média móvel para suavizar leituras ruidosas */
void hard();


/* ====================== IMPLEMENTAÇÃO ====================== */


#define POT_PIN ADC1_CHANNEL_6  // GPIO34

void base()
{
    // Configurar ADC
    adc1_config_width(ADC_WIDTH_BIT_12);  // 0-4095
    adc1_config_channel_atten(POT_PIN, ADC_ATTEN_DB_11);  // 0-3.3V
    
    while(1) {
        int raw_value = adc1_get_raw(POT_PIN);
        float voltage = (raw_value / 4095.0) * 3.3;
        
        printf("Raw: %d, Voltage: %.2fV\n", raw_value, voltage);
        
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

/* ====================== DESAFIOS ====================== */

void ease(){}

void medium(){}

void hard(){}

