/*
  Projeto: Sensor de Temperatura com LM35 - Básico
  Autor: Pirado
  Descrição:
    Mede a temperatura ambiente usando o sensor LM35
    e exibe o valor no monitor serial em graus Celsius.
*/

const int sensorPin = A0;
float temperatura;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int leitura = analogRead(sensorPin);
  temperatura = leitura * (5.0 / 1023.0) * 100.0;
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" °C");
  delay(1000);
}
