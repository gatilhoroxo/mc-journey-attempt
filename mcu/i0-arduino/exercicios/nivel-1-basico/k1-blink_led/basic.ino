/*
  Projeto: Blink LED Básico
  Autor: Pirado
  Descrição:
    Faz o LED do pino 13 piscar em intervalos de 1 segundo.
*/


#define led 9

void setup() {
  pinMode(led, OUTPUT);  // Define o pino 9 como saída
}

void loop() {
  digitalWrite(led, HIGH);  // Liga o LED
  delay(1000);             // Espera 1 segundo
  digitalWrite(led, LOW);   // Desliga o LED
  delay(1000);             // Espera 1 segundo
}
