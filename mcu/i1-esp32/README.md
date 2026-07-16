# i1-esp32/

ESP32 - Microcontrolador com WiFi/Bluetooth integrado.

---

## 📑 Índice

1. [📂 Estrutura](#-estrutura)
2. [🎯 Objetivo](#-objetivo)
3. [📌 Por Que Começar com ESP32?](#-por-que-começar-com-esp32)
4. [🔧 Setup e Configuração](#-setup-e-configuração)
5. [📚 Conteúdo por Nível](#-conteúdo-por-nível)
6. [📖 Referências Específicas ESP32](#-referências-específicas-esp32)
7. [💡 Dicas Específicas ESP32](#-dicas-específicas-esp32)
8. [🔗 Próximo Passo](#-próximo-passo)

---

## 📂 Estrutura
```
i1-esp32/
├── README.md              # 👈 Você está aqui
├── pins_esp32_38pins.jpg  # Pinout do modelo 38 pinos
├── j1-exercicios/         # Exercícios progressivos
│   ├── README.md
│   ├── nivel-1-basico/
│   ├── nivel-2-intermediario/
│   └── nivel-3-avancado/
└── j2-projetos/           # Projetos completos
    └── README.md
```

## 🎯 Objetivo

Dominar GPIO, comunicação e recursos wireless usando ESP-IDF (framework oficial).

**Por que ESP32?**
- WiFi/Bluetooth nativos
- Dual-core (2 CPUs ARM Xtensa)
- 38 pinos GPIO (no modelo usado)
- ADC, DAC, PWM, I2C, SPI, UART
- Documentação abundante
- Comunidade gigante

---

## 📌 Por Que Começar com ESP32?

Pense no ESP32 como o **Monkey D. Luffy** dos microcontroladores: é poderoso, versátil, tem muitos recursos (WiFi, Bluetooth, dual-core), mas também é amigável para quem está começando. Assim como o Luffy não sabia usar Haki no início mas tinha potencial, você vai começar com o básico e aos poucos destrava recursos mais avançados!

### Vantagens do ESP32
- ✅ Documentação abundante (inclusive em português)
- ✅ WiFi/Bluetooth nativos
- ✅ Dual-core (duas CPUs!)
- ✅ 38 pinos GPIO no seu modelo
- ✅ ADC, DAC, PWM, I2C, SPI, UART
- ✅ Comunidade gigante
- ✅ ESP-IDF (framework oficial) é muito completo

### Desvantagens (Para Aprender)
- ⚠️ Pode abstrair demais alguns conceitos
- ⚠️ Muitos recursos podem confundir no início

---

## 🔧 Setup e Configuração

### Hardware Necessário
- ESP32 38 pinos
- Cabo USB (geralmente micro-USB)
- Protoboard
- Componentes eletrônicos básicos

### Instalação do Ambiente (Semana 1-2)

#### Opção 1: ESP-IDF (Recomendado para C Puro)
```bash
# Linux/Mac
git clone -b v5.1 --recursive https://github.com/espressif/esp-idf.git
cd esp-idf
./install.sh esp32
. ./export.sh

# Windows: Use o instalador oficial
# https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/windows-setup.html
```

#### Opção 2: PlatformIO (Mais Amigável)
```bash
# Instale via VS Code Extension
# Depois crie projeto com framework ESP-IDF
```

### Seu Primeiro "Hello World"

```c
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main(void)
{
    printf("Hello from ESP32!\n");
    
    while(1) {
        printf("ESP32 rodando...\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS); // 1 segundo
    }
}
```

**Compile e grave:**
```bash
idf.py build
idf.py -p /dev/ttyUSB0 flash monitor
```

---

## 📚 Conteúdo por Nível

### Nível 1 - Básico
- GPIO (input/output)
- PWM (controle de LED)
- ADC (leitura analógica)
- Serial (UART)
- Blink LED, botões, sensores simples

### Nível 2 - Intermediário
- Interrupts (ISR)
- I2C (sensores/displays)
- SPI (comunicação rápida)
- WiFi básico (conexão, HTTP)
- Projetos com conectividade

### Nível 3 - Avançado
- FreeRTOS (tasks, queues, semaphores)
- Dual-core programming
- Bluetooth (BLE)
- OTA (atualização remota)
- Otimização de energia

---

## 📖 Referências Específicas ESP32

### Documentação Essencial
1. [**ESP-IDF Programming Guide**](https://docs.espressif.com/projects/esp-idf/en/latest/)
2. **ESP32 Technical Reference Manual** - Hardware detalhado
3. **ESP32 Datasheet** - Specs elétricas

### Livros
- ["Kolban's Book on ESP32" - Neil Kolban](https://roberthart56.github.io/SCFAB/SC_lab/Electronics/Microcontrollers/ESP32/kolban-ESP32.pdf)
- "ESP32 for Makers" - Pratik Desai (não encongrei)

### Canais YouTube (PT-BR)
- Brincando com Ideias - [Temporada ESP32](https://www.youtube.com/playlist?list=PL7CjOZ3q8fMdgvaq988L97y05Gb219fLd)
- [WR Kits](https://www.youtube.com/results?search_query=esp32+WR+Kits+playlist)
- [Fernando K Tecnologia](https://www.youtube.com/playlist?list=PL_xGnxKCyJXrup_lH20Yfsvi5pIL_9l9f)

### GitHub Exemplos
- https://github.com/espressif/esp-idf/tree/master/examples

---

## 💡 Dicas Específicas ESP32

### GPIO Especiais
- GPIO34-39: Input only (sem pull-up interno!)
- GPIO0: Boot (deve estar HIGH no boot)
- GPIO2: LED interno
- Strapping pins: evite usar sem necessidade

### Consumo de Energia
- Deep sleep pode durar dias com bateria
- Light sleep para economia moderada
- Use WiFi apenas quando necessário

### Debugging
```bash
# Monitor serial
idf.py monitor

# Monitor com filtro
idf.py monitor | grep "ERROR"

# Ver logs de crash
idf.py monitor decode
```

---

## 🔗 Próximo Passo

Após completar o **Nível 2** aqui, siga para:
- **[../i2-rp2040-a/](../i2-rp2040-a/)** - RP2040 com PIO e dual-core ARM

Ou consulte:
- **Roadmap geral:** [`roadmap_geral.md`](../../docs/roadmaps/roadmap_geral.md)
- **Referências:** [`REFERENCIAS.md`](../../docs/referencias/REFERENCIAS.md)
- **Voltar:** [`README.md`](../README.md)

---

**Status atual:** Em planejamento

**Pré-requisito:** Completar Arduino Nível 2
