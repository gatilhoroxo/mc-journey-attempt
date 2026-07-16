# 🔗 projetos-integrados/

Projetos que utilizam múltiplos microcontroladores trabalhando juntos.

---

## 📑 Índice

1. [📂 Estrutura](#-estrutura)
2. [🎯 Pré-requisitos](#-pré-requisitos)
3. [💡 Conceitos Abordados](#-conceitos-abordados)
4. [📚 Projetos](#-projetos)
5. [🚀 Quando Começar](#-quando-começar)

---

## 📂 Estrutura

```
projetos-integrados/
├── README.md                         # 👈 Você está aqui
├── projeto-1-automacao-residencial/  # Sistema de automação
│   └── README.md
└── projeto-2-robo-distribuido/       # Robô com múltiplos MCUs
    └── README.md
```

## 🎯 Pré-requisitos

**Necessário completar pelo menos Nível 2** de cada MCU que será usado no projeto:

- ✅ **Arduino** - Nível 2 (Intermediário)
- ✅ **ESP32** - Nível 2 (Intermediário)
- ✅ **RP2040** - Nível 2 (Intermediário)
- ✅ **STM8** - Nível 2 (Intermediário)

**Conhecimentos essenciais:**
- Comunicação I2C/SPI/UART
- Protocolos de sincronização
- Debugging multi-dispositivo

## 💡 Conceitos Abordados

### Comunicação entre MCUs
- UART (serial assíncrona)
- I2C (master/slave)
- SPI (high-speed)
- Protocolos customizados

### Arquitetura Distribuída
- Divisão de tarefas
- Gateway patterns
- Master/Slave architecture
- Peer-to-peer communication

### Sincronização
- Timestamps
- Heartbeat/watchdog
- Event-driven communication
- Message queues

### Segurança e Confiabilidade
- Checksum/CRC
- Retry mechanisms
- Fallback strategies
- Error handling

## 📚 Projetos

### Projeto 1: Automação Residencial
**Objetivo:** Sistema completo de automação usando múltiplos MCUs

**MCUs utilizados:**
- **ESP32** - Gateway WiFi (interface web, MQTT)
- **RP2040** - Controlador de sensores (temperatura, umidade, movimento)
- **STM8** - Controle crítico (relés, acionamentos)

**Features:**
- Controle via app web
- Sensores distribuídos
- Automações programadas
- Logs e monitoramento

**Detalhes:** [`projeto-1-automacao-residencial/README.md`](projeto-1-automacao-residencial/README.md)

### Projeto 2: Robô Distribuído
**Objetivo:** Robô com processamento distribuído

**MCUs utilizados:**
- **ESP32** - Comunicação e controle principal
- **RP2040** - Controle de motores (PIO)
- **Arduino** - Leitura de sensores

**Features:**
- Navegação autônoma
- Controle remoto
- Múltiplos sensores
- Coordenação entre MCUs

**Detalhes:** [`projeto-2-robo-distribuido/README.md`](projeto-2-robo-distribuido/README.md)

## 🚀 Quando Começar

**Recomendação:** Somente após completar:
1. [`../mcu/i1-esp32/`](../mcu/i1-esp32/) - Nível 2
2. [`../mcu/i2-rp2040-a/`](../mcu/i2-rp2040-a/) - Nível 2
3. Pelo menos um projeto individual de cada MCU

**Habilidades necessárias:**
- Debugging multi-dispositivo
- Leitura de osciloscópio/analisador lógico
- Paciência e persistência!

---

## 🔗 Links Relacionados

- **MCUs individuais:** [`../mcu/`](../mcu/)
- **Roadmap geral:** [`../learn/roadmap_geral.md`](../learn/roadmap_geral.md)
- **Templates:** [`../learn/i5-templates/`](../learn/i5-templates/)
- **Voltar:** [`../README.md`](../README.md)

---

**Status:** Em planejamento

**Estimativa:** Iniciar após semana 30-35 do roadmap
