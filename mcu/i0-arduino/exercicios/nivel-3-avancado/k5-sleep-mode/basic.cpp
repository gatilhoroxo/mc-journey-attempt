#include "Arduino.h"
#include <avr/sleep.h>
#include <avr/power.h>

const int LED_PIN = 13;
const int BUTTON_PIN = 2;

volatile bool wakeUpFlag = false;

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  // Configurar interrupt externo (wake-up)
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), wakeUp, FALLING);
  
  Serial.println("Sistema iniciado");
  Serial.println("Pressione botão para acordar do sleep");
}

void wakeUp() {
  // ISR para wake-up
  // Apenas seta flag
  wakeUpFlag = true;
}

void enterSleep() {
  Serial.println("Entrando em Power-down mode...");
  Serial.flush();  // Aguarda envio completo
  
  // Configurar sleep mode
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  
  // Desabilitar periféricos (economia extra)
  power_adc_disable();      // ADC
  power_spi_disable();      // SPI
  power_timer0_disable();   // Timer0 (millis/delay)
  power_timer1_disable();   // Timer1
  power_timer2_disable();   // Timer2
  power_twi_disable();      // I2C
  
  // Entrar em sleep (CPU para aqui até interrupt)
  sleep_mode();
  
  // === ACORDOU! ===
  sleep_disable();
  
  // Reabilitar periféricos
  power_all_enable();
  
  Serial.println("Acordei!");
}

void loop() {
  if (wakeUpFlag) {
    wakeUpFlag = false;
    
    // Piscar LED 3x
    for (int i = 0; i < 3; i++) {
      digitalWrite(LED_PIN, HIGH);
      delay(200);
      digitalWrite(LED_PIN, LOW);
      delay(200);
    }
    
    // Aguardar 5 segundos
    Serial.println("Voltando a dormir em 5 segundos...");
    delay(5000);
  }
  
  // Entrar em sleep
  enterSleep();
}

// ===== MEDIÇÃO DE CONSUMO =====
void measurePower() {
  Serial.println("\n=== TESTE DE CONSUMO ===");
  
  // Ativo
  Serial.println("Modo ATIVO (LED piscando)");
  Serial.println("Meça corrente agora (5s)...");
  unsigned long start = millis();
  while (millis() - start < 5000) {
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    delay(500);
  }
  
  // Sleep
  Serial.println("\nModo POWER-DOWN");
  Serial.println("Meça corrente agora (10s)...");
  Serial.flush();
  delay(100);
  
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  power_all_disable();
  
  delay(10000);  // Sleep por 10s (usando WDT seria melhor)
  
  sleep_disable();
  power_all_enable();
  
  Serial.println("Fim do teste");
}
