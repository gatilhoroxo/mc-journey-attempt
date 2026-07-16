// Exercício 18: PWM com Registradores Timer1
// Controle preciso de PWM usando Timer1

#define LED_PIN 9  // OC1A (PB1)

void setup() {
  Serial.begin(9600);
  
  Serial.println(F("=== PWM com Timer1 ==="));
  Serial.println(F("Escolha uma opção:"));
  Serial.println(F("1 - Fast PWM 8-bit"));
  Serial.println(F("2 - Fast PWM 10-bit"));
  Serial.println(F("3 - PWM Customizado (1kHz)"));
  Serial.println(F("4 - Fade automático"));
  
  // Configurar pino como OUTPUT
  DDRB |= (1 << DDB1);  // PB1 (pino 9)
}

void loop() {
  if (Serial.available()) {
    char option = Serial.read();
    
    switch (option) {
      case '1':
        setupFastPWM8bit();
        Serial.println(F("Fast PWM 8-bit configurado (7.8kHz)"));
        break;
        
      case '2':
        setupFastPWM10bit();
        Serial.println(F("Fast PWM 10-bit configurado (1.95kHz)"));
        break;
        
      case '3':
        setupCustomPWM(1000, 50);  // 1kHz, 50% duty
        Serial.println(F("PWM customizado: 1kHz, 50% duty"));
        break;
        
      case '4':
        fadeDemo();
        break;
        
      default:
        Serial.println(F("Opção inválida"));
        break;
    }
  }
}

// ===== FAST PWM 8-BIT =====
void setupFastPWM8bit() {
  // Timer1 Fast PWM mode 5 (8-bit, TOP=0x00FF)
  // WGM13:0 = 0101
  
  TCCR1A = (1 << COM1A1)  // Clear OC1A on compare, set at BOTTOM
         | (1 << WGM10);  // WGM10 = 1
  
  TCCR1B = (1 << WGM12)   // WGM12 = 1
         | (1 << CS11);   // Prescaler = 8
  
  OCR1A = 128;  // 50% duty cycle
  
  // Freq = 16MHz / (8 × 256) = 7812.5 Hz
}

// ===== FAST PWM 10-BIT =====
void setupFastPWM10bit() {
  // Timer1 Fast PWM mode 7 (10-bit, TOP=0x03FF)
  // WGM13:0 = 0111
  
  TCCR1A = (1 << COM1A1)  // Clear OC1A on compare
         | (1 << WGM11)   // WGM11 = 1
         | (1 << WGM10);  // WGM10 = 1
  
  TCCR1B = (1 << WGM12)   // WGM12 = 1
         | (1 << CS11);   // Prescaler = 8
  
  OCR1A = 512;  // 50% duty cycle
  
  // Freq = 16MHz / (8 × 1024) = 1953.125 Hz
}

// ===== PWM CUSTOMIZADO =====
void setupCustomPWM(uint32_t frequency, uint8_t dutyCycle) {
  // Timer1 Fast PWM mode 14 (ICR1 = TOP)
  // WGM13:0 = 1110
  
  TCCR1A = (1 << COM1A1)  // Non-inverting mode
         | (1 << WGM11);  // WGM11 = 1
  
  TCCR1B = (1 << WGM13)   // WGM13 = 1
         | (1 << WGM12)   // WGM12 = 1
         | (1 << CS11);   // Prescaler = 8
  
  // Calcular TOP para frequência desejada
  // Freq = F_CPU / (Prescaler × (1 + TOP))
  // TOP = (F_CPU / (Prescaler × Freq)) - 1
  
  uint16_t top = (F_CPU / (8UL * frequency)) - 1;
  ICR1 = top;
  
  // Duty cycle
  OCR1A = (top * dutyCycle) / 100;
  
  Serial.print(F("TOP = "));
  Serial.println(top);
  Serial.print(F("OCR1A = "));
  Serial.println(OCR1A);
  Serial.print(F("Freq real = "));
  Serial.print((float)F_CPU / (8UL * (1 + top)));
  Serial.println(F(" Hz"));
}

// ===== DEMO FADE =====
void fadeDemo() {
  Serial.println(F("Fade demo iniciado..."));
  setupFastPWM8bit();
  
  for (int cycle = 0; cycle < 3; cycle++) {
    // Fade in
    for (int i = 0; i < 256; i++) {
      OCR1A = i;
      delay(5);
    }
    
    // Fade out
    for (int i = 255; i >= 0; i--) {
      OCR1A = i;
      delay(5);
    }
  }
  
  Serial.println(F("Fade demo concluído"));
}
