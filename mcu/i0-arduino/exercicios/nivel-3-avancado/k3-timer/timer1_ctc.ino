// Exercício 19: Timer1 Interrupt (CTC Mode)
// Execução precisa de tarefas periódicas

#include <avr/interrupt.h>

#define LED_PIN 13

volatile bool ledState = false;
volatile uint32_t secondsCounter = 0;
volatile uint16_t millisCounter = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  
  Serial.println(F("=== Timer1 Interrupt ==="));
  Serial.println(F("LED pisca a cada 1 segundo (sem delay!)"));
  
  setupTimer1Interrupt(1);  // 1 Hz (1 segundo)
  
  Serial.println(F("Timer configurado"));
}

void loop() {
  // Loop fica livre para outras tarefas!
  
  static uint32_t lastPrint = 0;
  
  if (secondsCounter != lastPrint) {
    lastPrint = secondsCounter;
    
    Serial.print(F("Uptime: "));
    printTime(secondsCounter);
    Serial.print(F(" - Free RAM: "));
    Serial.print(freeRam());
    Serial.println(F(" bytes"));
  }
  
  // Simular outras tarefas
  if (Serial.available()) {
    char cmd = Serial.read();
    
    if (cmd == 'r') {
      Serial.println(F("Reset contador"));
      secondsCounter = 0;
    } else if (cmd == 's') {
      printStats();
    }
  }
}

// ===== CONFIGURAR TIMER1 CTC MODE =====
void setupTimer1Interrupt(uint16_t frequencyHz) {
  cli();  // Desabilitar interrupts
  
  // 1. Resetar Timer1
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  
  // 2. Configurar CTC mode (Clear Timer on Compare)
  //    WGM12 = 1 (CTC mode, TOP = OCR1A)
  TCCR1B |= (1 << WGM12);
  
  // 3. Configurar Prescaler = 1024
  //    CS12 = 1, CS10 = 1
  TCCR1B |= (1 << CS12) | (1 << CS10);
  
  // 4. Calcular OCR1A
  //    F_interrupt = F_CPU / (Prescaler × (1 + OCR1A))
  //    OCR1A = (F_CPU / (Prescaler × F_interrupt)) - 1
  
  uint32_t ocrValue = (F_CPU / (1024UL * frequencyHz)) - 1;
  
  if (ocrValue > 65535) {
    Serial.println(F("ERRO: Frequência muito baixa!"));
    ocrValue = 65535;
  }
  
  OCR1A = ocrValue;
  
  // 5. Habilitar interrupt por comparação A
  TIMSK1 |= (1 << OCIE1A);
  
  sei();  // Reabilitar interrupts
  
  Serial.print(F("OCR1A = "));
  Serial.println(ocrValue);
  Serial.print(F("Freq real: "));
  Serial.print((float)F_CPU / (1024UL * (1 + ocrValue)), 6);
  Serial.println(F(" Hz"));
}

// ===== ISR - TIMER1 COMPARE A =====
ISR(TIMER1_COMPA_vect) {
  // Executado a cada 1 segundo
  
  // Toggle LED
  ledState = !ledState;
  digitalWrite(LED_PIN, ledState);
  
  // Incrementar contador
  secondsCounter++;
}

// ===== FUNÇÕES AUXILIARES =====

void printTime(uint32_t seconds) {
  uint16_t hours = seconds / 3600;
  uint8_t minutes = (seconds % 3600) / 60;
  uint8_t secs = seconds % 60;
  
  if (hours < 10) Serial.print('0');
  Serial.print(hours);
  Serial.print(':');
  if (minutes < 10) Serial.print('0');
  Serial.print(minutes);
  Serial.print(':');
  if (secs < 10) Serial.print('0');
  Serial.print(secs);
}

int freeRam() {
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

void printStats() {
  Serial.println(F("\n=== ESTATÍSTICAS ==="));
  Serial.print(F("Uptime: "));
  printTime(secondsCounter);
  Serial.println();
  Serial.print(F("Free RAM: "));
  Serial.print(freeRam());
  Serial.println(F(" bytes"));
  Serial.print(F("Estado LED: "));
  Serial.println(ledState ? F("ON") : F("OFF"));
  Serial.println(F("==================\n"));
}
