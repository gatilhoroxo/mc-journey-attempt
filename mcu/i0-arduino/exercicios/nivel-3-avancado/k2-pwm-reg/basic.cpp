#include "Arduino.h"

// PWM Fast Mode com Timer1 no pino 9 (OC1A)

void setup() {
  Serial.begin(9600);
  
  // ===== COMPARAÇÃO: analogWrite() vs Timer1 =====
  
  // MÉTODO ARDUINO (abstração):
  // pinMode(9, OUTPUT);
  // analogWrite(9, 128);  // 50% duty cycle
  // Frequência: ~490Hz (Timer1)
  
  // ===== MÉTODO REGISTRADORES (Timer1 Fast PWM) =====
  
  // 1. Configurar pino 9 (PB1) como OUTPUT
  DDRB |= (1 << DDB1);
  
  // 2. Configurar Timer1 para Fast PWM, 8-bit (modo 5)
  //    WGM13:0 = 0101 (Fast PWM, TOP = 0x00FF)
  TCCR1A = (1 << COM1A1)  // Clear OC1A on compare match, set at BOTTOM
         | (1 << WGM10);  // WGM10 = 1
  
  TCCR1B = (1 << WGM12)   // WGM12 = 1 (modo Fast PWM 8-bit)
         | (1 << CS11);   // Prescaler = 8
  
  // 3. Definir duty cycle (0-255)
  OCR1A = 128;  // 50% duty cycle
  
  // Frequência PWM = 16MHz / (8 × 256) = 7.8kHz
  
  Serial.println("PWM Timer1 configurado:");
  Serial.print("Frequência: ");
  Serial.print(16000000UL / (8 * 256));
  Serial.println(" Hz");
  Serial.print("Duty Cycle: ");
  Serial.print((OCR1A * 100) / 255);
  Serial.println("%");
}

void loop() {
  // Fade usando Timer1
  for (int i = 0; i < 256; i++) {
    OCR1A = i;  // Atualiza duty cycle
    delay(10);
  }
  for (int i = 255; i >= 0; i--) {
    OCR1A = i;
    delay(10);
  }
}

// ===== PWM COM FREQUÊNCIA CUSTOMIZADA =====
void setupCustomPWM(uint32_t frequency, uint8_t dutyCycle) {
  // Calcular prescaler e TOP para frequência desejada
  // Exemplo: 1kHz PWM
  
  DDRB |= (1 << DDB1);  // PB1 (pino 9) como OUTPUT
  
  // Timer1 CTC mode com toggle OC1A
  TCCR1A = (1 << COM1A1);  // Non-inverting mode
  TCCR1B = (1 << WGM12)    // CTC mode
         | (1 << CS11);    // Prescaler 8
  
  // TOP para 1kHz: 16MHz / (8 × 2 × 1000) - 1 = 999
  uint16_t top = (F_CPU / (8UL * frequency)) - 1;
  ICR1 = top;
  
  // Duty cycle
  OCR1A = (top * dutyCycle) / 100;
  
  Serial.print("PWM customizado: ");
  Serial.print(frequency);
  Serial.print(" Hz, ");
  Serial.print(dutyCycle);
  Serial.println("% duty cycle");
}
