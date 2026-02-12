/*
  Projeto: Sensor de Temperatura com LM35 - Melhorado
  Autor: Pirado
  Descrição:
    Mede a temperatura ambiente usando o sensor LM35,
    exibe em um display LCD 16x2 e envia também via Serial.
    (Opcional: grava os dados em um cartão SD, se disponível.)
*/

#include <LiquidCrystal.h>
#include <SD.h>

const int sensorPin = A0;
const int chipSelect = 10; // Pino CS do módulo SD (caso utilizado)

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

float temperatura;
File logFile;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("Sensor LM35");

  // Inicializa o SD (opcional)
  if (SD.begin(chipSelect)) {
    Serial.println("Cartão SD pronto.");
  } else {
    Serial.println("Falha ao inicializar SD.");
  }
  delay(1000);
  lcd.clear();
}

void loop() {
  int leitura = analogRead(sensorPin);
  temperatura = leitura * (5.0 / 1023.0) * 100.0;

  // Exibe no LCD
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperatura);
  lcd.print(" C   ");

  // Envia via Serial
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" °C");

  // Grava no SD (opcional)
  if (SD.begin(chipSelect)) {
    logFile = SD.open("temp_log.txt", FILE_WRITE);
    if (logFile) {
      logFile.print("Temperatura: ");
      logFile.print(temperatura);
      logFile.println(" °C");
      logFile.close();
    }
  }

  delay(1000);
}
