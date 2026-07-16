// ===== PROJETO FINAL: Sistema de Aquisição de Dados =====
// 
// Funcionalidades:
// - Leitura de sensor BME280 (temp, umidade, pressão)
// - Timestamp com RTC DS3231
// - Log em cartão SD (CSV)
// - Display LCD com menu
// - Alarmes configuráveis
// - Sleep mode para economia de energia
//
// Autor: [Seu Nome]
// Data: 27/12/2025

#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <RTClib.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
#include <avr/sleep.h>
#include <avr/power.h>

#include "config.h"

// ===== OBJETOS GLOBAIS =====
RTC_DS3231 rtc;
Adafruit_BME280 bme;
LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLS, LCD_ROWS);

// ===== VARIÁVEIS DE ESTADO =====
struct SensorData {
  float temperature;
  float humidity;
  float pressure;
  uint8_t status;
};

struct SystemConfig {
  uint32_t interval_ms;
  float temp_alarm;
  float humidity_alarm;
  uint8_t timestamp_format;
};

SensorData lastReading;
SystemConfig config;

volatile bool btnMenuPressed = false;
volatile bool btnSelectPressed = false;
volatile bool timeToRead = false;

uint8_t menuState = 0;
uint8_t menuIndex = 0;
bool isLogging = false;

unsigned long lastReadTime = 0;
unsigned long lastLcdUpdate = 0;

// ===== PROTÓTIPOS =====
void loadConfig();
void saveConfig();
void readSensors();
void logToSD(const SensorData& data);
void updateDisplay();
void handleMenu();
void setStatusLED(uint8_t status);
void checkAlarms(const SensorData& data);
void enterSleepMode();

// ===== ISRs =====
void btnMenuISR() {
  static unsigned long lastInterrupt = 0;
  unsigned long interruptTime = millis();
  
  if (interruptTime - lastInterrupt > DEBOUNCE_DELAY_MS) {
    btnMenuPressed = true;
  }
  lastInterrupt = interruptTime;
}

void btnSelectISR() {
  static unsigned long lastInterrupt = 0;
  unsigned long interruptTime = millis();
  
  if (interruptTime - lastInterrupt > DEBOUNCE_DELAY_MS) {
    btnSelectPressed = true;
  }
  lastInterrupt = interruptTime;
}

// ===== SETUP =====
void setup() {
  #if DEBUG_SERIAL
  Serial.begin(SERIAL_BAUD);
  delay(1000);
  Serial.println(F("=== Sistema de Aquisição de Dados ==="));
  #endif
  
  // Configurar pinos
  pinMode(LED_R_PIN, OUTPUT);
  pinMode(LED_G_PIN, OUTPUT);
  pinMode(LED_B_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BTN_MENU_PIN, INPUT_PULLUP);
  pinMode(BTN_SELECT_PIN, INPUT_PULLUP);
  
  // Inicializar I2C
  Wire.begin();
  
  // Inicializar LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(F("Iniciando..."));
  
  // Carregar configuração da EEPROM
  loadConfig();
  
  // Inicializar RTC
  if (!rtc.begin()) {
    DEBUG_PRINTLN(F("ERRO: RTC não encontrado!"));
    lcd.clear();
    lcd.print(F("ERRO: RTC"));
    setStatusLED(STATUS_ERROR);
    while (1);
  }
  
  if (rtc.lostPower()) {
    DEBUG_PRINTLN(F("RTC perdeu energia, ajustando..."));
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  
  // Inicializar BME280
  if (!bme.begin(BME280_ADDR)) {
    DEBUG_PRINTLN(F("ERRO: BME280 não encontrado!"));
    lcd.clear();
    lcd.print(F("ERRO: BME280"));
    setStatusLED(STATUS_ERROR);
    while (1);
  }
  
  // Configurar BME280
  bme.setSampling(Adafruit_BME280::MODE_FORCED,
                  Adafruit_BME280::SAMPLING_X1,
                  Adafruit_BME280::SAMPLING_X1,
                  Adafruit_BME280::SAMPLING_X1,
                  Adafruit_BME280::FILTER_OFF);
  
  // Inicializar SD Card
  if (!SD.begin(SD_CS_PIN)) {
    DEBUG_PRINTLN(F("ERRO: SD Card não encontrado!"));
    lcd.clear();
    lcd.print(F("ERRO: SD Card"));
    setStatusLED(STATUS_ERROR);
    while (1);
  }
  
  // Criar arquivo de log se não existir
  if (!SD.exists(LOG_FILENAME)) {
    File logFile = SD.open(LOG_FILENAME, FILE_WRITE);
    if (logFile) {
      logFile.println(F("timestamp,temperature_c,humidity_percent,pressure_hpa,status"));
      logFile.close();
      DEBUG_PRINTLN(F("Arquivo de log criado"));
    }
  }
  
  // Configurar interrupts
  attachInterrupt(digitalPinToInterrupt(BTN_MENU_PIN), btnMenuISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(BTN_SELECT_PIN), btnSelectISR, FALLING);
  
  // Status OK
  setStatusLED(STATUS_OK);
  lcd.clear();
  lcd.print(F("Sistema OK"));
  delay(1000);
  
  DEBUG_PRINTLN(F("Sistema iniciado com sucesso!"));
}

// ===== LOOP PRINCIPAL =====
void loop() {
  unsigned long currentTime = millis();
  
  // Verificar se é hora de ler sensores
  if (isLogging && (currentTime - lastReadTime >= config.interval_ms)) {
    readSensors();
    logToSD(lastReading);
    checkAlarms(lastReading);
    lastReadTime = currentTime;
  }
  
  // Atualizar display
  if (currentTime - lastLcdUpdate >= LCD_REFRESH_MS) {
    updateDisplay();
    lastLcdUpdate = currentTime;
  }
  
  // Tratar botões
  if (btnMenuPressed) {
    btnMenuPressed = false;
    handleMenu();
  }
  
  if (btnSelectPressed) {
    btnSelectPressed = false;
    // Toggle logging
    isLogging = !isLogging;
    if (isLogging) {
      DEBUG_PRINTLN(F("Logging iniciado"));
      lastReadTime = currentTime - config.interval_ms; // Ler imediatamente
    } else {
      DEBUG_PRINTLN(F("Logging pausado"));
    }
  }
  
  // Sleep mode (opcional - comentado para manter responsivo)
  // if (!isLogging && menuState == 0) {
  //   enterSleepMode();
  // }
}

// ===== FUNÇÕES =====

void loadConfig() {
  uint16_t magic;
  EEPROM.get(EEPROM_MAGIC_ADDR, magic);
  
  if (magic == EEPROM_MAGIC_VALUE) {
    // Configuração válida
    EEPROM.get(EEPROM_INTERVAL_ADDR, config.interval_ms);
    EEPROM.get(EEPROM_TEMP_ALARM_ADDR, config.temp_alarm);
    EEPROM.get(EEPROM_HUM_ALARM_ADDR, config.humidity_alarm);
    EEPROM.get(EEPROM_FORMAT_ADDR, config.timestamp_format);
    DEBUG_PRINTLN(F("Configuração carregada da EEPROM"));
  } else {
    // Usar padrões
    config.interval_ms = DEFAULT_INTERVAL_MS;
    config.temp_alarm = TEMP_ALARM_C;
    config.humidity_alarm = HUMIDITY_ALARM;
    config.timestamp_format = TIMESTAMP_FORMAT_ISO8601;
    saveConfig();
    DEBUG_PRINTLN(F("Configuração padrão aplicada"));
  }
}

void saveConfig() {
  uint16_t magic = EEPROM_MAGIC_VALUE;
  EEPROM.put(EEPROM_MAGIC_ADDR, magic);
  EEPROM.put(EEPROM_INTERVAL_ADDR, config.interval_ms);
  EEPROM.put(EEPROM_TEMP_ALARM_ADDR, config.temp_alarm);
  EEPROM.put(EEPROM_HUM_ALARM_ADDR, config.humidity_alarm);
  EEPROM.put(EEPROM_FORMAT_ADDR, config.timestamp_format);
  DEBUG_PRINTLN(F("Configuração salva na EEPROM"));
}

void readSensors() {
  bme.takeForcedMeasurement();
  
  lastReading.temperature = bme.readTemperature();
  lastReading.humidity = bme.readHumidity();
  lastReading.pressure = bme.readPressure() / 100.0F; // Pa para hPa
  lastReading.status = STATUS_OK;
  
  DEBUG_PRINT(F("T:"));
  DEBUG_PRINT(lastReading.temperature);
  DEBUG_PRINT(F(" H:"));
  DEBUG_PRINT(lastReading.humidity);
  DEBUG_PRINT(F(" P:"));
  DEBUG_PRINTLN(lastReading.pressure);
}

void logToSD(const SensorData& data) {
  File logFile = SD.open(LOG_FILENAME, FILE_WRITE);
  
  if (logFile) {
    DateTime now = rtc.now();
    
    // Timestamp
    char timestamp[32];
    snprintf(timestamp, sizeof(timestamp), "%04d-%02d-%02d %02d:%02d:%02d",
             now.year(), now.month(), now.day(),
             now.hour(), now.minute(), now.second());
    
    logFile.print(timestamp);
    logFile.print(',');
    logFile.print(data.temperature, 2);
    logFile.print(',');
    logFile.print(data.humidity, 2);
    logFile.print(',');
    logFile.print(data.pressure, 2);
    logFile.print(',');
    
    switch (data.status) {
      case STATUS_OK:       logFile.println(F("OK")); break;
      case STATUS_WARNING:  logFile.println(F("WARNING")); break;
      case STATUS_ERROR:    logFile.println(F("ERROR")); break;
      default:              logFile.println(F("UNKNOWN")); break;
    }
    
    logFile.close();
    DEBUG_PRINTLN(F("Log gravado no SD"));
  } else {
    DEBUG_PRINTLN(F("ERRO ao abrir arquivo de log"));
    setStatusLED(STATUS_ERROR);
  }
}

void updateDisplay() {
  if (menuState == 0) {
    // Tela principal
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(F("T:"));
    lcd.print(lastReading.temperature, 1);
    lcd.print(F("C H:"));
    lcd.print((int)lastReading.humidity);
    lcd.print(F("%"));
    
    lcd.setCursor(0, 1);
    lcd.print(F("P:"));
    lcd.print((int)lastReading.pressure);
    lcd.print(F("hPa "));
    lcd.print(isLogging ? F("LOG") : F("---"));
  }
  // Adicionar mais telas de menu aqui
}

void handleMenu() {
  menuState++;
  if (menuState > 3) menuState = 0;
  
  lcd.clear();
  switch (menuState) {
    case 0:
      lcd.print(F("Tela Principal"));
      break;
    case 1:
      lcd.print(F("Config"));
      break;
    case 2:
      lcd.print(F("Estatisticas"));
      break;
    case 3:
      lcd.print(F("Sobre"));
      lcd.setCursor(0, 1);
      lcd.print(F("v1.0 - 2025"));
      break;
  }
  delay(1000);
}

void setStatusLED(uint8_t status) {
  switch (status) {
    case STATUS_OK:
      analogWrite(LED_R_PIN, 0);
      analogWrite(LED_G_PIN, 255);
      analogWrite(LED_B_PIN, 0);
      break;
    case STATUS_WARNING:
      analogWrite(LED_R_PIN, 255);
      analogWrite(LED_G_PIN, 255);
      analogWrite(LED_B_PIN, 0);
      break;
    case STATUS_ERROR:
      analogWrite(LED_R_PIN, 255);
      analogWrite(LED_G_PIN, 0);
      analogWrite(LED_B_PIN, 0);
      break;
    case STATUS_LOGGING:
      analogWrite(LED_R_PIN, 0);
      analogWrite(LED_G_PIN, 0);
      analogWrite(LED_B_PIN, 255);
      break;
  }
}

void checkAlarms(const SensorData& data) {
  bool alarm = false;
  
  if (data.temperature > config.temp_alarm) {
    DEBUG_PRINTLN(F("ALARME: Temperatura alta!"));
    alarm = true;
    lastReading.status = STATUS_WARNING;
  }
  
  if (data.humidity > config.humidity_alarm) {
    DEBUG_PRINTLN(F("ALARME: Umidade alta!"));
    alarm = true;
    lastReading.status = STATUS_WARNING;
  }
  
  if (alarm) {
    setStatusLED(STATUS_WARNING);
    // Buzzer (opcional)
    tone(BUZZER_PIN, 1000, 200);
  } else {
    setStatusLED(isLogging ? STATUS_LOGGING : STATUS_OK);
  }
}

void enterSleepMode() {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_mode();
  sleep_disable();
}
