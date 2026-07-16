// Exercício 22: Watchdog Timer
// Reset automático e wake-up periódico

#include <avr/wdt.h>
#include <avr/sleep.h>

#define LED_PIN 13

volatile int wdtCounter = 0;
volatile bool wdtFlag = false;

void setup() {
  Serial.begin(9600);
  
  // Desabilitar watchdog (pode ter sido habilitado pelo bootloader)
  wdt_disable();
  
  pinMode(LED_PIN, OUTPUT);
  
  delay(2000);
  
  Serial.println(F("\n=== WATCHDOG TIMER DEMO ==="));
  Serial.println(F("1 - Reset por timeout"));
  Serial.println(F("2 - Wake-up periódico"));
  Serial.println(F("3 - Failsafe (detectar travamento)"));
  Serial.println(F("\nEnvie '1', '2' ou '3'..."));
}

void loop() {
  if (Serial.available()) {
    char cmd = Serial.read();
    
    switch (cmd) {
      case '1':
        demoWatchdogReset();
        break;
        
      case '2':
        demoWatchdogWakeup();
        break;
        
      case '3':
        demoFailsafe();
        break;
        
      default:
        break;
    }
  }
  
  // Processar wake-up do WDT
  if (wdtFlag) {
    wdtFlag = false;
    
    Serial.print(F("Wake-up #"));
    Serial.println(wdtCounter);
    
    // Piscar LED
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
  }
}

// ===== DEMO 1: Watchdog Reset =====
void demoWatchdogReset() {
  Serial.println(F("\n--- Demo 1: Watchdog Reset ---"));
  Serial.println(F("Habilitando WDT com timeout 2s"));
  Serial.println(F("Sistema vai RESETAR em 2s"));
  Serial.println(F("(Não vou chamar wdt_reset())"));
  Serial.flush();
  
  // Habilitar watchdog com timeout 2s
  wdt_enable(WDTO_2S);
  
  // Piscar LED sem alimentar watchdog
  while (true) {
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    delay(500);
    
    // Normalmente faria:
    // wdt_reset();  // "Alimenta" watchdog (evita reset)
    // Mas aqui NÃO vamos fazer, então vai resetar em 2s
  }
  
  // Nunca chega aqui (reset acontece)
}

// ===== DEMO 2: Watchdog Wake-up =====
void demoWatchdogWakeup() {
  Serial.println(F("\n--- Demo 2: Watchdog Wake-up ---"));
  Serial.println(F("WDT vai acordar MCU a cada 8s"));
  Serial.println(F("LED pisca ao acordar"));
  Serial.println(F("(Pressione RESET para sair)\n"));
  Serial.flush();
  
  // Configurar WDT para interrupt (não reset)
  setupWatchdogInterrupt(WDTO_8S);
  
  // Loop infinito: sleep → wake → piscar → sleep
  while (true) {
    Serial.print(F("Sleep... (acordar em 8s) - Counter: "));
    Serial.println(wdtCounter);
    Serial.flush();
    
    // Entrar em power-down
    enterPowerDown();
    
    // === ACORDOU! ===
    Serial.println(F("Acordei!"));
    
    // Piscar LED
    for (int i = 0; i < 3; i++) {
      digitalWrite(LED_PIN, HIGH);
      delay(100);
      digitalWrite(LED_PIN, LOW);
      delay(100);
    }
  }
}

// ===== DEMO 3: Failsafe =====
void demoFailsafe() {
  Serial.println(F("\n--- Demo 3: Failsafe ---"));
  Serial.println(F("WDT habilitado com timeout 4s"));
  Serial.println(F("Travamento simulado após 10s"));
  Serial.flush();
  
  wdt_enable(WDTO_4S);
  
  unsigned long startTime = millis();
  
  while (true) {
    // Tarefas normais
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    delay(500);
    
    // "Alimentar" watchdog (evita reset)
    wdt_reset();
    
    // Simular travamento após 10 segundos
    if (millis() - startTime > 10000) {
      Serial.println(F("\n!!! TRAVAMENTO SIMULADO !!!"));
      Serial.println(F("Parei de chamar wdt_reset()"));
      Serial.println(F("Watchdog vai RESETAR em 4s..."));
      Serial.flush();
      
      // Parar de alimentar watchdog
      while (true) {
        // Loop infinito → reset em 4s
        delay(100);
      }
    }
    
    // Mostrar status
    if ((millis() - startTime) % 2000 == 0) {
      Serial.print(F("Sistema OK - Tempo: "));
      Serial.print((millis() - startTime) / 1000);
      Serial.println(F("s"));
    }
  }
}

// ===== CONFIGURAR WDT INTERRUPT MODE =====
void setupWatchdogInterrupt(uint8_t timeout) {
  cli();  // Desabilitar interrupts
  
  wdt_reset();  // Resetar watchdog
  
  // Configurar WDT para interrupt mode (não reset)
  // WDTCSR = Watchdog Timer Control Register
  
  // 1. Habilitar mudança de configuração (WDCE)
  WDTCSR |= (1 << WDCE) | (1 << WDE);
  
  // 2. Configurar timeout e modo interrupt
  //    WDIE = 1 (interrupt enable)
  //    WDE = 0 (system reset disable)
  WDTCSR = (1 << WDIE) | timeout;
  
  sei();  // Reabilitar interrupts
}

// ===== ENTRAR EM POWER-DOWN =====
void enterPowerDown() {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_mode();
  sleep_disable();  // Executa após acordar
}

// ===== ISR WATCHDOG =====
ISR(WDT_vect) {
  // Executado ao acordar do WDT
  wdtCounter++;
  wdtFlag = true;
}
