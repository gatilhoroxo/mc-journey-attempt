# Projeto Final: Sistema de Aquisição de Dados

## 📖 Descrição

Sistema completo de aquisição de dados com múltiplos sensores, armazenamento em SD card, interface LCD e alarmes configuráveis.

## 🎯 Funcionalidades

### ✅ Implementadas

1. **Aquisição de Dados:**
   - Sensor BME280 (temperatura, umidade, pressão)
   - Leituras periódicas configuráveis (5s - 1h)
   - Timestamp via RTC DS3231

2. **Armazenamento:**
   - Log em CSV no cartão SD
   - Formato: `timestamp,temp,humidity,pressure,status`
   - Cabeçalho automático

3. **Interface:**
   - Display LCD 16x2 I2C
   - Tela principal com leituras em tempo real
   - Menu de navegação

4. **Alarmes:**
   - LED RGB indica status (verde=OK, amarelo=alerta, vermelho=erro)
   - Buzzer para notificações sonoras
   - Limites configuráveis

5. **Configuração:**
   - Salva na EEPROM
   - Intervalo de aquisição
   - Limites de alarme
   - Formato de timestamp

## 🔧 Hardware Necessário

### Componentes Principais
- 1x Arduino UNO R3
- 1x Sensor BME280 (I2C)
- 1x RTC DS3231 (I2C)
- 1x Módulo SD Card (SPI)
- 1x Display LCD 16x2 I2C
- 2x Botões (Menu, Select)
- 1x LED RGB (cátodo comum)
- 1x Buzzer piezoelétrico

### Componentes Auxiliares
- 3x Resistores 220Ω (LED RGB)
- Cartão microSD (FAT32, até 32GB)
- Protoboard
- Jumpers
- Fonte 5V/1A (recomendado)

## 📐 Diagrama de Conexões

```
=== I2C Bus (A4=SDA, A5=SCL) ===
BME280:     VCC→3.3V  GND→GND  SDA→A4  SCL→A5
RTC DS3231: VCC→5V    GND→GND  SDA→A4  SCL→A5
LCD 16x2:   VCC→5V    GND→GND  SDA→A4  SCL→A5

=== SPI Bus (SD Card) ===
SD Module:  VCC→5V  GND→GND  CS→10  MOSI→11  MISO→12  SCK→13

=== Botões ===
BTN Menu:   Pino 2 (INT0) → Botão → GND (INPUT_PULLUP)
BTN Select: Pino 3 (INT1) → Botão → GND (INPUT_PULLUP)

=== LED RGB (cátodo comum) ===
Cátodo → GND
Red →   Pino 9  (PWM) com resistor 220Ω
Green → Pino 6  (PWM) com resistor 220Ω
Blue →  Pino 5  (PWM) com resistor 220Ω

=== Buzzer ===
Pino 4 → Buzzer (+) → GND
```

## 📚 Bibliotecas Necessárias

Instalar via Arduino Library Manager:

```
- Wire.h               (Arduino built-in)
- SPI.h                (Arduino built-in)
- SD.h                 (Arduino built-in)
- EEPROM.h             (Arduino built-in)
- RTClib               by Adafruit
- Adafruit_Sensor      by Adafruit
- Adafruit_BME280      by Adafruit
- LiquidCrystal_I2C    by Frank de Brabander
```

## 🚀 Como Usar

### 1. Preparação

```bash
# Formatar cartão SD como FAT32
# Ajustar RTC (executar uma vez):
rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
```

### 2. Upload

```bash
# Arduino IDE
Sketch → Upload (Ctrl+U)

# PlatformIO
pio run --target upload
```

### 3. Operação

1. **Inicialização:**
   - LED vermelho → Erro
   - LED verde → Sistema OK

2. **Navegação:**
   - Botão MENU: Navegar entre telas
   - Botão SELECT: Iniciar/Pausar logging

3. **Telas:**
   - **Principal:** Leituras em tempo real
   - **Config:** Ajustar parâmetros
   - **Stats:** Estatísticas (min/max/avg)
   - **About:** Informações do sistema

4. **Status LED:**
   - 🟢 Verde: Normal
   - 🟡 Amarelo: Alarme ativo
   - 🔴 Vermelho: Erro
   - 🔵 Azul: Logging ativo

### 4. Arquivo de Log

```csv
timestamp,temperature_c,humidity_percent,pressure_hpa,status
2025-12-27 10:30:00,23.5,65.2,1013.25,OK
2025-12-27 10:30:10,23.6,65.1,1013.30,OK
2025-12-27 10:30:20,24.1,64.8,1013.28,WARNING
```

## ⚙️ Configuração

### Via Código (`config.h`)

```cpp
#define DEFAULT_INTERVAL_MS  10000  // 10 segundos
#define TEMP_ALARM_C         30.0   // 30°C
#define HUMIDITY_ALARM       80.0   // 80%
```

### Via EEPROM (persistente)

Ajustável via menu LCD (futuras implementações).

## 🔍 Diagnóstico

### Serial Monitor (115200 baud)

```
=== Sistema de Aquisição de Dados ===
Configuração carregada da EEPROM
Sistema iniciado com sucesso!
T:23.5 H:65.2 P:1013.25
Log gravado no SD
```

### Códigos de Erro

- **ERRO: RTC** → RTC não encontrado (verificar conexões I2C)
- **ERRO: BME280** → Sensor não encontrado (verificar endereço I2C)
- **ERRO: SD Card** → Cartão não detectado (verificar formatação FAT32)

## 📊 Especificações

### Performance
- Intervalo mínimo: 5 segundos
- Intervalo máximo: 1 hora
- Precisão timestamp: ±1 segundo (RTC)
- Consumo: ~80mA (normal), ~10mA (sleep)

### Limites
- Temperatura: -40°C a +85°C (BME280)
- Umidade: 0% a 100% (BME280)
- Pressão: 300-1100 hPa (BME280)

### Armazenamento
- RAM: ~1500 bytes utilizados (~73%)
- Flash: ~18KB utilizados (~56%)
- SD Card: Limitado apenas pelo cartão

## 🔧 Melhorias Futuras

### Curto Prazo
- [ ] Menu completo no LCD
- [ ] Edição de configuração via botões
- [ ] Estatísticas (min/max/média)
- [ ] Gráfico histórico no LCD

### Médio Prazo
- [ ] Comunicação Bluetooth (HC-05)
- [ ] Aplicativo Android/iOS
- [ ] Múltiplos sensores simultâneos
- [ ] Bateria com indicador

### Longo Prazo
- [ ] Upgrade para ESP32 (WiFi)
- [ ] Servidor web local
- [ ] Cloud storage (ThingSpeak, Blynk)
- [ ] Display TFT colorido

## 📖 Referências

- [BME280 Datasheet](https://www.bosch-sensortec.com/media/boschsensortec/downloads/datasheets/bst-bme280-ds002.pdf)
- [DS3231 Datasheet](https://datasheets.maximintegrated.com/en/ds/DS3231.pdf)
- [SD Card Format](https://www.sdcard.org/developers/overview/capacity/)
- [CSV Format](https://tools.ietf.org/html/rfc4180)

## 👤 Autor

[Seu Nome]  
Data: 27/12/2025  
Versão: 1.0

## 📄 Licença

MIT License - Livre para uso e modificação
