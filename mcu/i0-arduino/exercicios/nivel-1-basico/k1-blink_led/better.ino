/*
  Projeto: Blink LED Melhorado
  Autor: Pirado
  Descrição:
    Pisca o LED do pino 13 com velocidade ajustável por potenciômetro,
    usando millis() em vez de delay().
*/

#define ledPin 13;     // LED conectado ao pino 13
#define potPin A0;     // Potenciômetro conectado à entrada analógica A0

unsigned long tempoAnterior = 0; // Armazena o último momento em que o LED mudou
int intervalo = 500;             // Intervalo padrão (em ms)
bool estadoLED = false;          // Estado atual do LED

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(potPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // Lê o valor do potenciômetro (0 a 1023)
  int leituraPot = analogRead(potPin);

  // Converte o valor lido em um intervalo de tempo (100 a 2000 ms)
  intervalo = map(leituraPot, 0, 1023, 100, 2000);

  unsigned long tempoAtual = millis();

  // Se o intervalo de tempo passou, inverte o estado do LED
  if (tempoAtual - tempoAnterior >= (unsigned long)intervalo) {
    tempoAnterior = tempoAtual;
    estadoLED = !estadoLED;  // Inverte o estado
    digitalWrite(ledPin, estadoLED ? HIGH : LOW);
  }

  // Envia o valor atual ao monitor serial (para debug)
  Serial.print("Intervalo: ");
  Serial.print(intervalo);
  Serial.println(" ms");
}
