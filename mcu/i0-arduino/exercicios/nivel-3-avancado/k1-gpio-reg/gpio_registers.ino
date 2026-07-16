// Exercício 17: GPIO com Registradores
// Controle de LEDs usando manipulação direta de registradores

#define LED_RED_PIN    13  // PB5
#define LED_YELLOW_PIN 12  // PB4
#define LED_GREEN_PIN  11  // PB3
#define BUTTON_PIN     2   // PD2

void setup() {
  Serial.begin(9600);
  
  // ===== MÉTODO ARDUINO (abstração) =====
  // pinMode(13, OUTPUT);
  // pinMode(12, OUTPUT);
  // pinMode(11, OUTPUT);
  // pinMode(2, INPUT_PULLUP);
  
  // ===== MÉTODO REGISTRADORES (bare-metal) =====
  // Configura PB5, PB4, PB3 como OUTPUT
  DDRB |= (1 << DDB5) | (1 << DDB4) | (1 << DDB3);
  
  // Configura PD2 como INPUT com pull-up
  DDRD &= ~(1 << DDD2);   // INPUT
  PORTD |= (1 << PD2);    // Pull-up ativo
  
  Serial.println(F("Sistema iniciado (registradores)"));
  Serial.println(F("Pressione botão para efeito Knight Rider"));
  
  // Executar benchmark
  benchmark();
}

void loop() {
  // ===== LER BOTÃO =====
  // Arduino: if (digitalRead(2) == LOW)
  // Registradores:
  if (!(PIND & (1 << PD2))) {  // PD2 == 0 (botão pressionado)
    
    // ===== PADRÃO 1: Knight Rider =====
    knightRider();
    
  } else {
    
    // ===== PADRÃO 2: Todos piscando =====
    // Arduino: digitalWrite(13, HIGH); digitalWrite(12, HIGH); digitalWrite(11, HIGH);
    PORTB |= (1 << PB5) | (1 << PB4) | (1 << PB3);  // Liga todos
    delay(500);
    
    // Arduino: digitalWrite(13, LOW); digitalWrite(12, LOW); digitalWrite(11, LOW);
    PORTB &= ~((1 << PB5) | (1 << PB4) | (1 << PB3));  // Desliga todos
    delay(500);
  }
}

void knightRider() {
  // PB3 → PB4 → PB5 → PB4 → PB3
  for (int i = 3; i <= 5; i++) {
    PORTB = (1 << i);  // Liga apenas um LED
    delay(150);
  }
  for (int i = 4; i >= 3; i--) {
    PORTB = (1 << i);
    delay(150);
  }
}

// ===== BENCHMARK: Arduino vs Registradores =====
void benchmark() {
  unsigned long start, duration;
  const int ITERATIONS = 10000;
  
  Serial.println(F("\n=== BENCHMARK ==="));
  
  // Teste Arduino digitalWrite
  start = micros();
  for (int i = 0; i < ITERATIONS; i++) {
    digitalWrite(13, HIGH);
    digitalWrite(13, LOW);
  }
  duration = micros() - start;
  Serial.print(F("digitalWrite ("));
  Serial.print(ITERATIONS);
  Serial.print(F(" iterações): "));
  Serial.print(duration);
  Serial.println(F(" us"));
  
  // Teste Registradores
  start = micros();
  for (int i = 0; i < ITERATIONS; i++) {
    PORTB |= (1 << PB5);
    PORTB &= ~(1 << PB5);
  }
  unsigned long regDuration = micros() - start;
  Serial.print(F("Registradores ("));
  Serial.print(ITERATIONS);
  Serial.print(F(" iterações): "));
  Serial.print(regDuration);
  Serial.println(F(" us"));
  
  Serial.print(F("Speedup: "));
  Serial.print((float)duration / regDuration);
  Serial.println(F("x mais rápido!"));
  Serial.println();
}
