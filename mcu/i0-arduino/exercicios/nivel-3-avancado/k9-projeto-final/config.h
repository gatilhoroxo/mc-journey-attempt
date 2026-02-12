// ===== CONFIGURAÇÕES DO SISTEMA =====

#ifndef CONFIG_H
#define CONFIG_H

// ===== PINOS =====
// I2C (Hardware)
#define SDA_PIN         A4
#define SCL_PIN         A5

// SPI (SD Card)
#define SD_CS_PIN       10
#define SD_MOSI_PIN     11
#define SD_MISO_PIN     12
#define SD_SCK_PIN      13

// Botões
#define BTN_MENU_PIN    2   // INT0
#define BTN_SELECT_PIN  3   // INT1

// LED RGB
#define LED_R_PIN       9   // PWM
#define LED_G_PIN       6   // PWM
#define LED_B_PIN       5   // PWM

// Buzzer
#define BUZZER_PIN      4

// ===== ENDEREÇOS I2C =====
#define BME280_ADDR     0x76  // ou 0x77
#define RTC_ADDR        0x68
#define LCD_ADDR        0x27  // ou 0x3F

// ===== CONFIGURAÇÕES DE AQUISIÇÃO =====
#define DEFAULT_INTERVAL_MS  10000  // 10 segundos
#define MIN_INTERVAL_MS      5000   // 5 segundos
#define MAX_INTERVAL_MS      3600000 // 1 hora

// ===== LIMITES DE ALARME =====
#define TEMP_MIN_C      -10.0
#define TEMP_MAX_C      50.0
#define TEMP_ALARM_C    30.0

#define HUMIDITY_MIN    0.0
#define HUMIDITY_MAX    100.0
#define HUMIDITY_ALARM  80.0

#define PRESSURE_MIN    900.0
#define PRESSURE_MAX    1100.0

// ===== EEPROM ADDRESSES =====
#define EEPROM_MAGIC_ADDR       0   // 2 bytes - magic number
#define EEPROM_INTERVAL_ADDR    2   // 4 bytes - uint32_t
#define EEPROM_TEMP_ALARM_ADDR  6   // 4 bytes - float
#define EEPROM_HUM_ALARM_ADDR   10  // 4 bytes - float
#define EEPROM_FORMAT_ADDR      14  // 1 byte  - uint8_t

#define EEPROM_MAGIC_VALUE      0xABCD

// ===== STATUS LED COLORS =====
#define STATUS_OK           0  // Verde
#define STATUS_WARNING      1  // Amarelo
#define STATUS_ERROR        2  // Vermelho
#define STATUS_LOGGING      3  // Azul

// ===== NOMES DE ARQUIVOS =====
#define LOG_FILENAME        "datalog.csv"
#define CONFIG_FILENAME     "config.txt"
#define MAX_FILENAME_LEN    32

// ===== FORMATO DE TIMESTAMP =====
#define TIMESTAMP_FORMAT_ISO8601    0  // 2025-12-27T10:30:00
#define TIMESTAMP_FORMAT_UNIX       1  // 1735297800
#define TIMESTAMP_FORMAT_READABLE   2  // 27/12/2025 10:30:00

// ===== BUFFER SIZES =====
#define SERIAL_BUFFER_SIZE  128
#define CSV_LINE_BUFFER     256

// ===== DEBOUNCE =====
#define DEBOUNCE_DELAY_MS   50

// ===== DISPLAY =====
#define LCD_COLS            16
#define LCD_ROWS            2
#define LCD_REFRESH_MS      500

// ===== DEBUG =====
#define DEBUG_SERIAL        1  // 1 = habilitado, 0 = desabilitado
#define SERIAL_BAUD         115200

#if DEBUG_SERIAL
  #define DEBUG_PRINT(x)    Serial.print(x)
  #define DEBUG_PRINTLN(x)  Serial.println(x)
  #define DEBUG_PRINTF(...)  Serial.print(F(__VA_ARGS__))
#else
  #define DEBUG_PRINT(x)
  #define DEBUG_PRINTLN(x)
  #define DEBUG_PRINTF(...)
#endif

#endif // CONFIG_H
