# 🤖 Projeto 2: Robô Distribuído

Robô com processamento distribuído usando múltiplos microcontroladores.

---

## 📑 Índice

1. [🎯 Objetivo](#-objetivo)
2. [🏗️ Arquitetura](#️-arquitetura)
3. [📦 Componentes](#-componentes)
4. [📋 Fases do Projeto](#-fases-do-projeto)
5. [🔗 Comunicação](#-comunicação)

---

## 🎯 Objetivo

Construir um robô móvel onde diferentes microcontroladores assumem tarefas específicas:
- ESP32: Controle principal e comunicação WiFi
- RP2040: Controle de motores (usando PIO)
- Arduino: Leitura de sensores e navegação

**Nível:** ⭐⭐⭐⭐ Muito Avançado  
**Tempo estimado:** 60-80 horas  
**Pré-requisitos:** Todos os MCUs Nível 2+

---

## 🏗️ Arquitetura

```
┌─────────────────────────────────────┐
│      ESP32 (Controle Central)       │
│  - Navegação de alto nível          │
│  - WiFi/Bluetooth                   │
│  - Processamento de decisões        │
│  - Interface de controle            │
└────────┬───────────────┬────────────┘
         │ I2C           │ UART
    ┌────▼────┐     ┌────▼────────┐
    │ RP2040  │     │   Arduino   │
    │ Motores │     │  Sensores   │
    │  - PIO  │     │  - Ultra    │
    │  - PWM  │     │  - IR       │
    │  - Enc  │     │  - IMU      │
    └─────────┘     └─────────────┘
```

---

## 📦 Componentes

### Microcontroladores
- 1x ESP32
- 1x RP2040 (Pico)
- 1x Arduino UNO ou Nano

### Motores e Controle
- 2x Motor DC com encoder
- 1x Ponte H (L298N ou similar)
- 1x Servo motor (câmera/sensor)

### Sensores
- 2x Ultrassônico HC-SR04
- 2x Sensor IR (linha/obstáculo)
- 1x IMU (MPU6050)
- 1x Encoder rotativo (odometria)

### Alimentação
- Bateria Li-Po 7.4V ou 11.1V
- Step-down 5V (para lógica)
- Step-down 3.3V (para ESP32/sensores)

### Estrutura
- Chassis robô 2WD/4WD
- Rodas com encoders
- Suportes para sensores

**Custo estimado:** R$ 350-500

---

## 📋 Fases do Projeto

### ⏳ Fase 1: Controle de Motores (Semanas 1-2)
**Responsável:** RP2040

**Tarefas:**
- [ ] PWM para controle de velocidade (PIO)
- [ ] Leitura de encoders
- [ ] PID para controle de velocidade
- [ ] Odometria básica
- [ ] Interface I2C para comandos

**Entregáveis:**
- Controle preciso de motores
- Feedback de velocidade
- API de movimento

**Arquivos:**
```
fase-1-motores/
├── README.md
├── src/
│   ├── main.c
│   ├── motor_pio.c/h
│   ├── encoder.c/h
│   └── pid.c/h
└── tests/
    └── motor_test.c
```

---

### ⏳ Fase 2: Sensores e Navegação (Semanas 3-4)
**Responsável:** Arduino

**Tarefas:**
- [ ] Leitura de ultrassônicos
- [ ] Leitura de sensores IR
- [ ] IMU para orientação
- [ ] Detecção de obstáculos
- [ ] Envio de dados via UART

**Entregáveis:**
- Sistema de sensoriamento completo
- Algoritmo de desvio de obstáculos
- Calibração de sensores

**Arquivos:**
```
fase-2-sensores/
├── README.md
├── src/
│   ├── main.ino
│   ├── ultrasonic.cpp/h
│   ├── ir_sensor.cpp/h
│   └── imu.cpp/h
└── calibration/
    └── sensor_cal.ino
```

---

### ⏳ Fase 3: Comunicação e Integração (Semanas 5-6)
**Responsável:** ESP32 + integração

**Tarefas:**
- [ ] Protocolo I2C com RP2040
- [ ] Protocolo UART com Arduino
- [ ] Máquina de estados de navegação
- [ ] Sincronização de dados
- [ ] Tratamento de falhas

**Entregáveis:**
- Sistema de comunicação robusto
- Integração funcional
- Diagrama de estados

**Arquivos:**
```
fase-3-integracao/
├── README.md
├── esp32/
│   └── src/
│       ├── main.c
│       ├── i2c_driver.c
│       └── uart_driver.c
├── protocol/
│   └── spec.md
└── docs/
    └── state-machine.md
```

---

### ⏳ Fase 4: Controle Remoto (Semanas 7-8)
**Responsável:** ESP32

**Tarefas:**
- [ ] Interface web de controle
- [ ] Telemetria em tempo real
- [ ] Modo manual vs autônomo
- [ ] Streaming de câmera (opcional)
- [ ] Controle por joystick/app

**Entregáveis:**
- App web funcional
- Modo manual e autônomo
- Dashboard de telemetria

**Arquivos:**
```
fase-4-controle/
├── README.md
├── web/
│   ├── index.html
│   ├── control.js
│   └── style.css
├── firmware/
│   └── wifi_server.c
└── mobile-app/
    └── (opcional)
```

---

### ⏳ Fase 5: Autonomia e IA (Semanas 9-10)
**Responsável:** ESP32 + RP2040

**Tarefas:**
- [ ] Mapeamento simples (grid)
- [ ] Pathfinding (A* ou similar)
- [ ] Seguir linha/parede
- [ ] Evitar obstáculos autônomo
- [ ] Retorno à base (opcional)

**Entregáveis:**
- Navegação autônoma funcional
- Algoritmos de IA implementados
- Demonstração em vídeo

**Arquivos:**
```
fase-5-autonomia/
├── README.md
├── algorithms/
│   ├── pathfinding.c
│   ├── mapping.c
│   └── obstacle_avoidance.c
├── tests/
│   └── autonomous_test.c
└── docs/
    └── algorithms.md
```

---

## 🔗 Comunicação

### I2C (ESP32 ↔ RP2040)

**Comandos de Movimento:**
```c
#define CMD_FORWARD   0x01
#define CMD_BACKWARD  0x02
#define CMD_TURN_LEFT 0x03
#define CMD_TURN_RIGHT 0x04
#define CMD_STOP      0x05
#define CMD_GET_ODOM  0x10
```

### UART (ESP32 ↔ Arduino)

**Formato de Dados:**
```
[HEADER][CMD][DATA_LEN][...DATA...][CHECKSUM]
```

---

## 📊 Progresso Geral

| Fase | Descrição | Status | Progresso |
|------|-----------|--------|-----------|
| 1 | Motores | ⚪ Não iniciado | ░░░░░░░░░░ 0% |
| 2 | Sensores | ⚪ Não iniciado | ░░░░░░░░░░ 0% |
| 3 | Integração | ⚪ Não iniciado | ░░░░░░░░░░ 0% |
| 4 | Controle Remoto | ⚪ Não iniciado | ░░░░░░░░░░ 0% |
| 5 | Autonomia | ⚪ Não iniciado | ░░░░░░░░░░ 0% |

**Total:** 0% concluído

---

## 🎥 Demos

- [ ] Controle manual via web
- [ ] Desvio autônomo de obstáculos
- [ ] Seguir linha preta
- [ ] Retorno à base

---

## 📖 Referências

- [PID Control Tutorial](URL)
- [A* Pathfinding](URL)
- [Robot Kinematics](URL)

---

**Início:** Não iniciado  
**Previsão de conclusão:** TBD  
**Status:** ⚪ Planejamento
