// ===== TESTE DE PERFORMANCE: Arduino vs Otimizado =====
// Exercício 24: Comparação de técnicas de otimização

#include <avr/pgmspace.h>

#define LED_PIN 13

// ===== TESTE 1: digitalWrite vs Direct Port =====

void testDigitalWrite() {
  unsigned long start = micros();
  
  for (uint32_t i = 0; i < 100000; i++) {
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(LED_PIN, LOW);
  }
  
  unsigned long duration = micros() - start;
  Serial.print("digitalWrite: ");
  Serial.print(duration);
  Serial.println(" us");
}

void testDirectPort() {
  unsigned long start = micros();
  
  for (uint32_t i = 0; i < 100000; i++) {
    PORTB |= (1 << PB5);   // HIGH
    PORTB &= ~(1 << PB5);  // LOW
  }
  
  unsigned long duration = micros() - start;
  Serial.print("Direct Port: ");
  Serial.print(duration);
  Serial.println(" us");
  Serial.print("Speedup: ");
  Serial.println((float)duration / duration);
}

// ===== TESTE 2: Funções vs Inline vs Macros =====

int slowFunction(int x) {
  return x * 2 + 1;
}

inline int fastFunction(int x) {
  return x * 2 + 1;
}

#define MACRO_FUNCTION(x) ((x) * 2 + 1)

void testFunctions() {
  volatile int result;
  unsigned long start;
  
  Serial.println("\n--- Teste 2: Functions ---");
  
  // Função normal
  start = micros();
  for (uint32_t i = 0; i < 100000; i++) {
    result = slowFunction(i);
  }
  Serial.print("Normal function: ");
  Serial.print(micros() - start);
  Serial.println(" us");
  
  // Inline function
  start = micros();
  for (uint32_t i = 0; i < 100000; i++) {
    result = fastFunction(i);
  }
  Serial.print("Inline function: ");
  Serial.print(micros() - start);
  Serial.println(" us");
  
  // Macro
  start = micros();
  for (uint32_t i = 0; i < 100000; i++) {
    result = MACRO_FUNCTION(i);
  }
  Serial.print("Macro: ");
  Serial.print(micros() - start);
  Serial.println(" us");
}

// ===== TESTE 3: Lookup Table vs Cálculo =====

// Tabela de senos (0-90°) em incrementos de 1°
const uint8_t sinTable[] PROGMEM = {
  0, 2, 4, 7, 9, 11, 13, 16, 18, 20, 22, 24, 27, 29, 31, 33,
  35, 37, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60, 62, 64, 66,
  68, 70, 72, 73, 75, 77, 79, 81, 82, 84, 86, 87, 89, 91, 92, 94,
  95, 97, 98, 100, 101, 102, 104, 105, 106, 108, 109, 110, 111, 112, 113, 114,
  115, 116, 117, 118, 119, 120, 121, 122, 122, 123, 124, 125, 125, 126, 126,
  127, 127, 127, 128, 128, 128, 128, 128, 128, 128, 127
};

void testLookupTable() {
  unsigned long start;
  volatile uint8_t result;
  
  Serial.println("\n--- Teste 3: Lookup Table ---");
  
  // Cálculo com sin()
  start = micros();
  for (uint16_t i = 0; i < 1000; i++) {
    float angle = (i % 90) * 0.017453; // rad
    result = sin(angle) * 128;
  }
  Serial.print("sin() calculation: ");
  Serial.print(micros() - start);
  Serial.println(" us");
  
  // Lookup table
  start = micros();
  for (uint16_t i = 0; i < 1000; i++) {
    uint8_t index = i % 90;
    result = pgm_read_byte(&sinTable[index]);
  }
  Serial.print("Lookup table: ");
  Serial.print(micros() - start);
  Serial.println(" us");
}

// ===== TESTE 4: String vs F() Macro =====

void testStringMemory() {
  Serial.println("\n--- Teste 4: String Memory ---");
  
  // RAM usage
  Serial.println("This string is in RAM");
  Serial.print("Free RAM: ");
  Serial.println(freeRam());
  
  // PROGMEM usage
  Serial.println(F("This string is in PROGMEM"));
  Serial.print(F("Free RAM: "));
  Serial.println(freeRam());
}

int freeRam() {
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

// ===== TESTE 5: Memory Alignment =====

struct UnalignedStruct {
  uint8_t a;   // 1 byte
  uint32_t b;  // 4 bytes
  uint8_t c;   // 1 byte
}; // Total: pode ser 12 bytes (com padding)

struct AlignedStruct {
  uint32_t b;  // 4 bytes
  uint8_t a;   // 1 byte
  uint8_t c;   // 1 byte
}; // Total: pode ser 8 bytes

void testAlignment() {
  Serial.println("\n--- Teste 5: Memory Alignment ---");
  Serial.print("Unaligned struct: ");
  Serial.print(sizeof(UnalignedStruct));
  Serial.println(" bytes");
  
  Serial.print("Aligned struct: ");
  Serial.print(sizeof(AlignedStruct));
  Serial.println(" bytes");
}

// ===== SETUP & LOOP =====

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  
  delay(2000);
  
  Serial.println(F("========================================"));
  Serial.println(F("  PERFORMANCE TESTING SUITE"));
  Serial.println(F("  Arduino UNO - ATmega328P"));
  Serial.println(F("========================================\n"));
  
  // Executar testes
  Serial.println("--- Teste 1: digitalWrite vs Registradores ---");
  testDigitalWrite();
  testDirectPort();
  
  delay(1000);
  testFunctions();
  
  delay(1000);
  testLookupTable();
  
  delay(1000);
  testStringMemory();
  
  delay(1000);
  testAlignment();
  
  Serial.println(F("\n========================================"));
  Serial.println(F("  TESTES CONCLUÍDOS"));
  Serial.println(F("========================================"));
}

void loop() {
  // Piscar LED para indicar que está funcionando
  digitalWrite(LED_PIN, !digitalRead(LED_PIN));
  delay(1000);
}
