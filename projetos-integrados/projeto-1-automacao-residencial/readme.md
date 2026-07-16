# 🏠 Projeto 1: Automação Residencial Distribuída

Sistema completo de automação residencial usando múltiplos microcontroladores.

---

## 📑 Índice

1. [🎯 Objetivo](#-objetivo)
2. [🏗️ Arquitetura](#️-arquitetura)
3. [📦 Componentes](#-componentes)
4. [📋 Fases do Projeto](#-fases-do-projeto)
5. [🔗 Comunicação](#-comunicação)

---

## 🎯 Objetivo

Criar um sistema de automação residencial distribuído onde múltiplos microcontroladores trabalham em conjunto para:
- Monitorar temperatura, umidade, luminosidade
- Controlar iluminação e tomadas
- Interface web para controle remoto
- Logs e histórico de dados
- Automações programadas

**Nível:** ⭐⭐⭐ Avançado  
**Tempo estimado:** 40-60 horas  
**Pré-requisitos:** ESP32 Nível 2 + RP2040 Nível 2 + STM8 Nível 2

---

## 🏗️ Arquitetura

```
┌─────────────────────────────────────────┐
│         ESP32 (Gateway WiFi)            │
│  - Interface Web                        │
│  - MQTT Broker/Client                   │
│  - Banco de dados (SD Card)             │
│  - Controle central                     │
└────────────┬────────────────────────────┘
             │ UART/I2C
             ├──────────────────┬──────────────────┐
             │                  │                  │
┌────────────▼────────┐ ┌───────▼──────────┐ ┌───▼─────────────┐
│   RP2040 (Sensores) │ │ RP2040 (Display) │ │ STM8 (Controle) │
│  - Temp/Umidade     │ │  - LCD/OLED      │ │  - Relés        │
│  - Movimento (PIR)  │ │  - Status visual │ │  - Acionamentos │
│  - Luminosidade     │ │  - Botões locais │ │  - Segurança    │
└─────────────────────┘ └──────────────────┘ └─────────────────┘
```

---

## 📦 Componentes

### Microcontroladores
- 1x ESP32 38 pinos (gateway)
- 2x RP2040 (sensores + interface)
- 1x STM8 (controle crítico)

### Sensores
- 2x DHT22 (temperatura/umidade)
- 1x LDR (luminosidade)
- 2x PIR (movimento)
- 1x MQ-2 (gás - opcional)

### Atuadores
- 4x Relé 5V
- 2x LED RGB (indicadores)
- 1x Buzzer (alarmes)

### Interface
- 1x Display LCD 16x2 I2C ou OLED
- 4x Botões físicos
- Interface web (HTML/CSS/JS)

### Outros
- Módulo SD Card
- Fonte 5V 3A
- Protoboard/PCB
- Conectores e fios

**Custo estimado:** R$ 250-350

---

## 📋 Fases do Projeto

### ✅ Fase 1: Sensores (Semanas 1-2)
**Responsável:** RP2040 #1

**Tarefas:**
- [x] Leitura de DHT22 via I2C
- [ ] Leitura de LDR (ADC)
- [ ] Detecção de movimento (PIR)
- [ ] Calibração de sensores
- [ ] Envio de dados via UART para ESP32

**Entregáveis:**
- Código funcional de leitura
- Protocolo de comunicação definido
- Testes unitários

**Arquivos:**
```
fase-1-sensores/
├── README.md
├── src/
│   ├── main.c
│   ├── dht22.c/h
│   ├── ldr.c/h
│   └── pir.c/h
└── tests/
```

---

### ⏳ Fase 2: Atuadores (Semanas 3-4)
**Responsável:** STM8

**Tarefas:**
- [ ] Controle de relés via GPIO
- [ ] PWM para dimmer (opcional)
- [ ] Proteção contra sobrecarga
- [ ] Watchdog timer
- [ ] Receber comandos via UART

**Entregáveis:**
- Sistema de controle seguro
- Feedback de estado
- Logs de acionamento

**Arquivos:**
```
fase-2-atuadores/
├── README.md
├── src/
│   ├── main.c
│   ├── relay_control.c/h
│   └── safety.c/h
└── docs/
    └── safety-protocol.md
```

---

### ⏳ Fase 3: Comunicação (Semanas 5-6)
**Responsável:** ESP32 + integração

**Tarefas:**
- [ ] Protocolo UART entre MCUs
- [ ] Broker MQTT local ou cloud
- [ ] Sincronização de dados
- [ ] Tratamento de erros
- [ ] Checksum/CRC

**Entregáveis:**
- Protocolo documentado
- Biblioteca de comunicação
- Testes de confiabilidade

**Arquivos:**
```
fase-3-comunicacao/
├── README.md
├── protocol.md
├── esp32/
│   └── src/
│       └── uart_handler.c
└── docs/
    └── message-format.md
```

---

### ⏳ Fase 4: Interface (Semanas 7-8)
**Responsável:** ESP32 (web) + RP2040 #2 (display)

**Tarefas:**
- [ ] Interface web (HTML/CSS/JS)
- [ ] WebSocket para tempo real
- [ ] Display LCD/OLED local
- [ ] Botões físicos
- [ ] Feedback visual (LEDs)

**Entregáveis:**
- App web funcional
- Interface local com display
- Manual do usuário

**Arquivos:**
```
fase-4-interface/
├── README.md
├── web/
│   ├── index.html
│   ├── style.css
│   └── app.js
├── display/
│   └── src/
│       └── oled_ui.c
└── manual/
    └── user-guide.md
```

---

### ⏳ Fase 5: Integração Final (Semanas 9-10)
**Responsável:** Todos

**Tarefas:**
- [ ] Integrar todos os módulos
- [ ] Testes de sistema completo
- [ ] Otimização de performance
- [ ] Tratamento de edge cases
- [ ] Documentação final

**Entregáveis:**
- Sistema completo funcional
- Documentação técnica
- Vídeo demonstrativo
- PCB design (opcional)

**Arquivos:**
```
fase-5-integracao/
├── README.md
├── firmware/
│   ├── esp32/
│   ├── rp2040-sensors/
│   ├── rp2040-display/
│   └── stm8-control/
├── docs/
│   ├── architecture.md
│   ├── api.md
│   └── troubleshooting.md
└── demo/
    └── video.mp4
```

---

## 🔗 Comunicação

### Protocolo UART (MCU ↔ ESP32)

**Formato:**
```
START | SENDER_ID | CMD | LENGTH | PAYLOAD | CHECKSUM | END
0xAA  | 1 byte    | 1B  | 1B     | N bytes | 1B       | 0x55
```

**Comandos:**
- `0x01` - Leitura de sensor
- `0x02` - Controle de relé
- `0x03` - Status request
- `0x04` - Alarme
- `0xFF` - Heartbeat

### MQTT Topics

```
home/sensors/temperature
home/sensors/humidity
home/sensors/motion
home/actuators/relay1
home/actuators/relay2
home/status/system
```

---

## 📊 Progresso Geral

| Fase | Descrição | Status | Progresso |
|------|-----------|--------|-----------|
| 1 | Sensores | 🟡 Em andamento | ████░░░░░░ 40% |
| 2 | Atuadores | ⚪ Não iniciado | ░░░░░░░░░░ 0% |
| 3 | Comunicação | ⚪ Não iniciado | ░░░░░░░░░░ 0% |
| 4 | Interface | ⚪ Não iniciado | ░░░░░░░░░░ 0% |
| 5 | Integração | ⚪ Não iniciado | ░░░░░░░░░░ 0% |

**Total:** 8% concluído

---

## 📖 Referências

- [ESP32 Web Server Tutorial](URL)
- [MQTT Protocol](URL)
- [I2C Communication](URL)

---

**Início:** 2025-12-26  
**Previsão de conclusão:** 2026-03-xx  
**Status:** 🟡 Em desenvolvimento
