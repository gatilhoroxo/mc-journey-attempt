#include "Arduino.h"
#include <avr/wdt.h>
#include <avr/sleep.h>

volatile int wdtCounter = 0;

void setup() {
  Serial.begin(9600);
  
  // Desabilitar watchdog (pode ter sido habilitado pelo bootloader)
  wdt_disable();
  
  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.println("\n=== WATCHDOG TIMER DEMO ===");
  Serial.println("1. Reset por timeout");
  Serial.println("2. Wake-up periódico");
  Serial.println("Envie '1' ou '2'...");
}

void loop() {
  if (Serial.available()) {
    char cmd = Serial.read();
    
    if (cmd == '1') {
      demoWatchdogReset();
    } else if (cmd == '2') {
      demoWatchdogWakeup();
    }
  }
}

// ===== DEMO 1: Watchdog Reset =====
void demoWatchdogReset() {
  Serial.println("\n--- Demo 1: Watchdog Reset ---");
  Serial.println("Habilitando WDT com timeout 2s");
  Serial.println("Sistema vai resetar em 2s (não vai fazer wdt_reset)");
  Serial.flush();
  
  // Habilitar watchdog com timeout 2s
  wdt_enable(WDTO_2S);
  
  // Piscar LED sem alimentar watchdog
  while (true) {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    delay(500);
    
    // Normalmente faria:
    // wdt_reset();  // "Alimenta" watchdog (evita reset)
    // Mas aqui NÃO vamos fazer, então vai resetar em 2s
  }
  
  // Nunca chega aqui (reset acontece)
}

// ===== DEMO 2: Watchdog Wake-up =====
void demoWatchdogWakeup() {
  Serial.println("\n--- Demo 2: Watchdog Wake-up ---");
  Serial.println("WDT vai acordar MCU a cada 8s");
  Serial.println("LED pisca ao acordar");
  Serial.flush();
  
  // Configurar WDT para interrupt (não reset)
  setupWatchdogInterrupt(WDTO_8S);
  
  // Loop infinito: sleep → wake → piscar → sleep
  while (true) {
    Serial.print("Sleep... (acordar em 8s) - Counter: ");
    Serial.println(wdtCounter);
    Serial.flush();
    
    // Entrar em power-down
    enterPowerDown();
    
    // === ACORDOU! ===
    Serial.println("Acordei!");
    
    // Piscar LED
    for (int i = 0; i < 3; i++) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(100);
      digitalWrite(LED_BUILTIN, LOW);
      delay(100);
    }
  }
}

void setupWatchdogInterrupt(uint8_t timeout) {
  // Desabilitar interrupts
  cli();
  
  // Resetar watchdog
  wdt_reset();
  
  // Configurar WDT para interrupt mode (não reset)
  // WDTCSR = Watchdog Timer Control Register
  
  // 1. Habilitar mudança de configuração (WDCE)
  WDTCSR |= (1 << WDCE) | (1 << WDE);
  
  // 2. Configurar timeout e modo interrupt
  //    WDIE = 1 (interrupt enable)
  //    WDE = 0 (system reset disable)
  WDTCSR = (1 << WDIE) | timeout;
  
  // Reabilitar interrupts
  sei();
}

void enterPowerDown() {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_mode();
  sleep_disable();  // Executa após acordar
}

// ISR Watchdog
ISR(WDT_vect) {
  // Executado ao acordar do WDT
  wdtCounter++;
}

// ===== FAILSAFE: Detectar Travamento =====
void failsafeDemo() {
  Serial.println("Failsafe habilitado");
  
  wdt_enable(WDTO_4S);  // Timeout 4s
  
  while (true) {
    // Tarefas normais
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    delay(500);
    
    // "Alimentar" watchdog (evita reset)
    wdt_reset();
    
    // Simular travamento após 10 segundos
    if (millis() > 10000) {
      Serial.println("TRAVAMENTO SIMULADO!");
      Serial.println("Watchdog vai resetar em 4s...");
      Serial.flush();
      
      // Parar de alimentar watchdog
      while (true);  // Loop infinito → reset em 4s
    }
  }
}
