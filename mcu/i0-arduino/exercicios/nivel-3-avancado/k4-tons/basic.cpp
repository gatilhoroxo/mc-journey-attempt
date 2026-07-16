#include "Arduino.h"

// Geração de tons com Timer2

// Notas musicais (Hz)
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_REST 0

void setup() {
  Serial.begin(9600);
  
  // Configurar pino 11 (OC2A) como OUTPUT
  DDRB |= (1 << DDB3);
  
  Serial.println("Gerador de tons iniciado");
}

void playTone(uint16_t frequency, uint16_t duration) {
  if (frequency == 0) {
    // Pausa
    stopTone();
    delay(duration);
    return;
  }
  
  // Calcular OCR2A para frequência desejada
  // Timer2 CTC mode, toggle OC2A
  // F_tone = F_CPU / (2 × Prescaler × (1 + OCR2A))
  // OCR2A = (F_CPU / (2 × Prescaler × F_tone)) - 1
  
  // Usar prescaler 64
  uint32_t ocrValue = (F_CPU / (2UL * 64UL * frequency)) - 1;
  
  if (ocrValue > 255) {
    // Frequência muito baixa para prescaler 64
    // Tentar prescaler 256
    ocrValue = (F_CPU / (2UL * 256UL * frequency)) - 1;
    
    if (ocrValue > 255) ocrValue = 255;
    
    // Prescaler 256
    TCCR2B = (1 << WGM22) | (1 << CS22) | (1 << CS21);
  } else {
    // Prescaler 64
    TCCR2B = (1 << WGM22) | (1 << CS22);
  }
  
  // CTC mode, toggle OC2A
  TCCR2A = (1 << COM2A0) | (1 << WGM21);
  OCR2A = ocrValue;
  
  delay(duration);
}

void stopTone() {
  TCCR2A = 0;
  TCCR2B = 0;
}

void loop() {
  // Tocar escala musical (Dó, Ré, Mi, Fá, Sol, Lá, Si, Dó)
  int melody[] = {
    NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4,
    NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5
  };
  
  int durations[] = {
    500, 500, 500, 500,
    500, 500, 500, 1000
  };
  
  for (int i = 0; i < 8; i++) {
    Serial.print("Nota: ");
    Serial.print(melody[i]);
    Serial.println(" Hz");
    
    playTone(melody[i], durations[i]);
    stopTone();
    delay(100);  // Pausa entre notas
  }
  
  delay(2000);  // Pausa antes de repetir
}

// ===== MELODIA: "Jingle Bells" =====
void playJingleBells() {
  int melody[] = {
    NOTE_E4, NOTE_E4, NOTE_E4, NOTE_REST,
    NOTE_E4, NOTE_E4, NOTE_E4, NOTE_REST,
    NOTE_E4, NOTE_G4, NOTE_C4, NOTE_D4, NOTE_E4
  };
  
  int durations[] = {
    250, 250, 500, 250,
    250, 250, 500, 250,
    250, 250, 250, 250, 1000
  };
  
  for (int i = 0; i < 13; i++) {
    playTone(melody[i], durations[i]);
    stopTone();
    delay(50);
  }
}
