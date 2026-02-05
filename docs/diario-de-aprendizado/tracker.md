---
title: Tracker de Progresso
---

# 📊 Tracker de Progresso

Acompanhamento detalhado do progresso em cada microcontrolador.

**Última atualização:** 2026-02-05

---

## 📈 Resumo Geral

| MCU | Exercícios | Projetos | Progresso | Status |
|-----|-----------|----------|-----------|--------|
| **Arduino** | 3/15 | 0/3 | ██░░░░░░░░ 20% | 🔴 De Lado |
| **ESP32** | 0/20 | 0/5 | ░░░░░░░░░░ 0% | 🟡 Iniciado |
| **RP2040-A** | 0/18 | 0/4 | ░░░░░░░░░░ 0% | ⚪ Não iniciado |
| **RP2040 Zero** | 0/12 | 0/3 | ░░░░░░░░░░ 0% | ⚪ Não iniciado |
| **STM8** | 0/15 | 0/2 | ░░░░░░░░░░ 0% | ⚪ Não iniciado |

**Total:** 3/80 exercícios (3.75%) | 0/17 projetos (0%)

---

## 🔷 Arduino (i0)

### Nível 1 - Básico
- [x] **k1-blink_led** - Piscar LED com delay e millis
- [x] **k2-botao-led** - Controle com botão e debounce
- [x] **k3-sensor_temperatura** - Leitura ADC e conversão
- [ ] **k4-pwm_led** - Controle de intensidade com PWM
- [ ] **k5-buzzer** - Sons e melodias

### Nível 2 - Intermediário
- [ ] **k1-interrupt** - Interrupções externas
- [ ] **k2-i2c_display** - Display LCD/OLED I2C
- [ ] **k3-spi_sd** - Cartão SD via SPI
- [ ] **k4-uart_communication** - Comunicação serial
- [ ] **k5-timer** - Timers e contadores

### Nível 3 - Avançado
- [ ] **k1-low_power** - Modos de economia de energia
- [ ] **k2-custom_library** - Criar biblioteca própria
- [ ] **k3-registers** - Manipulação direta de registradores
- [ ] **k4-bootloader** - Programação via bootloader
- [ ] **k5-optimization** - Otimização de código

### Projetos
- [ ] **Projeto 1** - Estação meteorológica (nível 1-2)
- [ ] **Projeto 2** - Controle de motor DC (nível 2)
- [ ] **Projeto 3** - Sistema de alarme (nível 2-3)

---

## 🔷 ESP32 (i1)

### Nível 1 - Básico
- [ ] **k1-blink_led** - GPIO básico
- [ ] **k2-button_input** - Leitura de botão
- [ ] **k3-pwm** - PWM para LED
- [ ] **k4-adc** - Leitura analógica
- [ ] **k5-uart** - Serial básica
- [ ] **k6-wifi_scan** - Escanear redes WiFi
- [ ] **k7-wifi_connect** - Conectar WiFi

### Nível 2 - Intermediário
- [ ] **k1-interrupts** - ISR e interrupts
- [ ] **k2-i2c** - Comunicação I2C
- [ ] **k3-spi** - Comunicação SPI
- [ ] **k4-http_client** - Cliente HTTP
- [ ] **k5-http_server** - Servidor web
- [ ] **k6-mqtt** - Protocolo MQTT
- [ ] **k7-ble_beacon** - Bluetooth Low Energy

### Nível 3 - Avançado
- [ ] **k1-freertos_tasks** - Multitarefa FreeRTOS
- [ ] **k2-dual_core** - Uso de ambos os cores
- [ ] **k3-ota** - Atualização remota
- [ ] **k4-deep_sleep** - Economia de energia
- [ ] **k5-websocket** - WebSocket em tempo real
- [ ] **k6-custom_protocol** - Protocolo customizado

### Projetos
- [ ] **Projeto 1** - Sensor IoT (temperatura/umidade WiFi)
- [ ] **Projeto 2** - Controle remoto (app web)
- [ ] **Projeto 3** - Gateway MQTT
- [ ] **Projeto 4** - BLE sensor beacon
- [ ] **Projeto 5** - Sistema de monitoramento

---

## 🔷 RP2040-A (i2)

### Nível 1 - Básico
- [ ] **k1-gpio** - GPIO básico
- [ ] **k2-pwm** - PWM com SDK
- [ ] **k3-adc** - ADC built-in
- [ ] **k4-uart** - Serial communication
- [ ] **k5-multicore_basic** - Uso básico de dual-core
- [ ] **k6-timer** - Timers hardware

### Nível 2 - Intermediário
- [ ] **k1-i2c** - Comunicação I2C
- [ ] **k2-spi** - Comunicação SPI
- [ ] **k3-dma** - Direct Memory Access
- [ ] **k4-pio_basic** - PIO state machine básica
- [ ] **k5-interrupts** - Interrupt handling
- [ ] **k6-flash_storage** - Gravação em flash

### Nível 3 - Avançado
- [ ] **k1-pio_advanced** - PIO para protocolo customizado
- [ ] **k2-multicore_optimization** - Otimização multicore
- [ ] **k3-usb_device** - USB device class
- [ ] **k4-bare_metal** - Sem SDK (bare metal)
- [ ] **k5-clock_config** - Configuração de clocks
- [ ] **k6-power_management** - Gerenciamento de energia

### Projetos
- [ ] **Projeto 1** - LED Matrix com PIO
- [ ] **Projeto 2** - Analisador lógico (PIO)
- [ ] **Projeto 3** - Controlador de motor (dual-core)
- [ ] **Projeto 4** - USB MIDI device

---

## 🔷 RP2040 Zero (i3)

### Nível 1 - Básico
- [ ] **k1-gpio_limited** - GPIO com pinos limitados
- [ ] **k2-battery_power** - Alimentação por bateria
- [ ] **k3-i2c_sensors** - Sensores I2C compactos
- [ ] **k4-low_power** - Modos de economia

### Nível 2 - Intermediário
- [ ] **k1-oled_display** - Display OLED pequeno
- [ ] **k2-imu_sensor** - Sensor de movimento (IMU)
- [ ] **k3-battery_monitor** - Monitoramento de bateria
- [ ] **k4-sleep_wake** - Sleep e wake-up

### Nível 3 - Avançado
- [ ] **k1-wearable_design** - Projeto wearable
- [ ] **k2-pcb_design** - PCB customizado
- [ ] **k3-3d_case** - Case impresso em 3D
- [ ] **k4-ultra_low_power** - Otimização extrema

### Projetos
- [ ] **Projeto 1** - Smartwatch simples
- [ ] **Projeto 2** - Sensor de atividade
- [ ] **Projeto 3** - Badge eletrônico

---

## 🔷 STM8 (i4)

### Nível 1 - Básico
- [ ] **k1-gpio_registers** - GPIO via registradores
- [ ] **k2-clock_config** - Configurar clock manual
- [ ] **k3-uart_bare** - UART sem biblioteca
- [ ] **k4-datasheet_read** - Exercício de leitura de datasheet
- [ ] **k5-blink_bare** - Blink sem framework

### Nível 2 - Intermediário
- [ ] **k1-timer_bare** - Timers via registradores
- [ ] **k2-interrupt_config** - Configurar interrupts
- [ ] **k3-adc_manual** - ADC manual
- [ ] **k4-pwm_timer** - PWM via timer
- [ ] **k5-i2c_bitbang** - I2C por software (bit-bang)

### Nível 3 - Avançado
- [ ] **k1-assembly_inline** - Assembly inline
- [ ] **k2-optimization** - Otimização extrema
- [ ] **k3-custom_bootloader** - Bootloader próprio
- [ ] **k4-eeprom_access** - Acesso EEPROM interna
- [ ] **k5-power_modes** - Todos os power modes

### Projetos
- [ ] **Projeto 1** - Controlador bare metal
- [ ] **Projeto 2** - Sensor ultra-eficiente

---

## 🔗 Projetos Integrados

- [ ] **Automação Residencial** (ESP32 + RP2040 + STM8)
- [ ] **Robô Distribuído** (ESP32 + RP2040 + Arduino)

---

## 📝 Notas

- ✅ = Concluído
- 🔄 = Em andamento
- ⏸️ = Pausado
- ❌ = Não funcionou / Revisar

### Legenda de Status
- 🟢 **Concluído** - 100%
- 🟡 **Em andamento** - 1-99%
- ⚪ **Não iniciado** - 0%
- 🔴 **Bloqueado** - Aguardando algo

---

**Como usar este tracker:**
1. Marque `[x]` quando completar um exercício/projeto
2. Atualize a data no topo
3. Adicione notas conforme necessário
4. Mantenha sincronizado com seu diário 

