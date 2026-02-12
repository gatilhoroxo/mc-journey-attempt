// Exercício 21: Sleep Modes (Power Down)
// Economia de energia com modos de sleep

#include <avr/sleep.h>
#include <avr/power.h>

#define LED_PIN 13
#define BUTTON_PIN 2

volatile bool wakeUpFlag = false;
uint32_t sleepCount = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  delay(2000);
  
  Serial.println(F("=== Power Management Demo ==="));
  Serial.println(F("Pressione botão para acordar do sleep"));
  Serial.println(F("Comandos: 's' = dormir, 'm' = medir consumo\n"));
  
  // Configurar interrupt externo
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), wakeUp, FALLING);
  
  printMenu();
}

void loop() {
  if (wakeUpFlag) {
    wakeUpFlag = false;
    sleepCount++;
    
    Serial.println(F("\n>>> ACORDEI! <<<"));
    Serial.print(F("Wake-up #"));
    Serial.println(sleepCount);
    
    // Piscar LED 3x
    for (int i = 0; i < 3; i++) {
      digitalWrite(LED_PIN, HIGH);
      delay(200);
      digitalWrite(LED_PIN, LOW);
      delay(200);
    }
    
    Serial.println(F("Voltando a dormir em 5 segundos..."));
    delay(5000);
  }
  
  // Processar comandos serial
  if (Serial.available()) {
    char cmd = Serial.read();
    
    switch (cmd) {
      case 's':
      case 'S':
        enterSleep();
        break;
        
      case 'm':
      case 'M':
        measurePower();
        break;
        
      case 'h':
      case 'H':
        printMenu();
        break;
        
      default:
        break;
    }
  }
  
  // Entrar em sleep automaticamente após 10 segundos
  static unsigned long lastActivity = millis();
  if (millis() - lastActivity > 10000) {
    lastActivity = millis();
    enterSleep();
  }
}

// ===== ISR WAKE-UP =====
void wakeUp() {
  // Apenas seta flag (ISR deve ser rápida!)
  wakeUpFlag = true;
}

// ===== ENTRAR EM SLEEP MODE =====
void enterSleep() {
  Serial.println(F("\n--- Entrando em POWER-DOWN mode ---"));
  Serial.print(F("Consumo esperado: ~0.1-0.5 mA"));
  Serial.println(F("\n(Aguarde envio completo)"));
  Serial.flush();
  delay(100);
  
  // Configurar sleep mode
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  
  // Desabilitar periféricos (economia extra)
  power_adc_disable();      // ADC
  power_spi_disable();      // SPI
  power_timer0_disable();   // Timer0 (millis/delay param de funcionar!)
  power_timer1_disable();   // Timer1
  power_timer2_disable();   // Timer2
  power_twi_disable();      // I2C
  
  // Entrar em sleep (CPU para aqui até interrupt)
  sleep_mode();
  
  // === ACORDOU! ===
  sleep_disable();
  
  // Reabilitar periféricos
  power_all_enable();
  
  Serial.println(F(">>> Periféricos reabilitados <<<"));
}

// ===== MEDIÇÃO DE CONSUMO =====
void measurePower() {
  Serial.println(F("\n=== TESTE DE CONSUMO ==="));
  Serial.println(F("Conecte multímetro em série com VIN"));
  Serial.println();
  
  // Teste 1: Modo ativo
  Serial.println(F("1. MODO ATIVO (LED piscando)"));
  Serial.println(F("   Meça corrente agora (10s)..."));
  Serial.println(F("   Esperado: ~40-50mA"));
  
  unsigned long start = millis();
  while (millis() - start < 10000) {
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    delay(500);
  }
  digitalWrite(LED_PIN, LOW);
  
  delay(2000);
  
  // Teste 2: Sleep mode
  Serial.println(F("\n2. MODO POWER-DOWN"));
  Serial.println(F("   Meça corrente agora (10s)..."));
  Serial.println(F("   Esperado: ~0.1-0.5mA"));
  Serial.flush();
  delay(100);
  
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  power_all_disable();
  
  // Sleep por ~10s (usando WDT seria mais preciso)
  for (int i = 0; i < 10; i++) {
    sleep_mode();
    delay(1000);
  }
  
  sleep_disable();
  power_all_enable();
  
  delay(1000);
  
  Serial.println(F("\n=== TESTE CONCLUÍDO ==="));
  Serial.println(F("Economia: ~99% de corrente!"));
  Serial.println();
}

// ===== MENU =====
void printMenu() {
  Serial.println(F("\n=== COMANDOS ==="));
  Serial.println(F("s - Entrar em sleep manualmente"));
  Serial.println(F("m - Medir consumo de energia"));
  Serial.println(F("h - Mostrar este menu"));
  Serial.println(F("===============\n"));
}

// ===== FREE RAM =====
int freeRam() {
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}
