#include "Arduino.h"

// Timer1 Interrupt - Piscar LED a cada 1 segundo (SEM delay!)

volatile bool ledState = false;
volatile uint32_t secondsCounter = 0;

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  
  setupTimer1Interrupt(1);  // 1 Hz (1 segundo)
  
  Serial.println("Timer1 Interrupt configurado (1Hz)");
}

void setupTimer1Interrupt(uint16_t frequencyHz) {
  // Desabilitar interrupts durante configuração
  cli();
  
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
  
  // 4. Calcular OCR1A para frequência desejada
  //    F_interrupt = 16MHz / (1024 × (1 + OCR1A))
  //    OCR1A = (16MHz / (1024 × F_interrupt)) - 1
  
  uint32_t ocrValue = (F_CPU / (1024UL * frequencyHz)) - 1;
  
  if (ocrValue > 65535) {
    Serial.println("ERRO: Frequência muito baixa!");
    ocrValue = 65535;
  }
  
  OCR1A = ocrValue;
  
  // 5. Habilitar interrupt por comparação A
  TIMSK1 |= (1 << OCIE1A);
  
  // 6. Reabilitar interrupts
  sei();
  
  Serial.print("OCR1A = ");
  Serial.println(ocrValue);
  Serial.print("Frequência real: ");
  Serial.print((float)F_CPU / (1024UL * (1 + ocrValue)));
  Serial.println(" Hz");
}

// ISR - Executada a cada 1 segundo
ISR(TIMER1_COMPA_vect) {
  // Toggle LED
  ledState = !ledState;
  digitalWrite(13, ledState);
  
  // Incrementar contador
  secondsCounter++;
}

void loop() {
  // Loop fica livre para outras tarefas!
  
  static uint32_t lastPrint = 0;
  
  if (secondsCounter != lastPrint) {
    lastPrint = secondsCounter;
    
    Serial.print("Uptime: ");
    Serial.print(secondsCounter);
    Serial.println(" segundos");
  }
  
  // Outras tarefas podem ser executadas aqui
  // sem afetar o timing do LED
}
