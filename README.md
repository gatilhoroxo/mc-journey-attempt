# 🎯 Microcontroladores - Do Zero ao Avançado

> Repositório de aprendizado progressivo sobre microcontroladores, com foco em documentação detalhada para iniciantes.

[![Status](https://img.shields.io/badge/status-em%20progresso-yellow)]()

---

## 📑 Índice / Navegação

1. [🚀 Início Rápido](#-início-rápido)
2. [📊 Progresso por MCU](#-progresso-por-mcu)
3. [📂 Estrutura do Repositório](#-estrutura-do-repositório)
4. [📖 Sistema de Navegação](#-sistema-de-navegação)
5. [📚 Sobre o Projeto](#-sobre-o-projeto)
6. [🎯 Objetivos](#-objetivos)
7. [🛠️ Hardware Disponível](#️-hardware-disponível)
8. [🔗 Links Rápidos](#-links-rápidos)
9. [📈 Progresso](#-progresso)

---

## 📊 Progresso por MCU

| MCU | Exercícios | Projetos | Progresso | Status |
|-----|-----------|----------|-----------|--------|
| **Arduino** | 3/15 | 0/3 | ██░░░░░░░░ 20% | 🔴 De Lado |
| **ESP32** | 0/20 | 0/5 | █░░░░░░░░░ 10% | 🟡 Iniciado |
| **RP2040-A** | 0/18 | 0/4 | ░░░░░░░░░░ 0% | ⚪ Não iniciado |
| **RP2040 Zero** | 0/12 | 0/3 | ░░░░░░░░░░ 0% | ⚪ Não iniciado |
| **STM8** | 0/15 | 0/2 | ░░░░░░░░░░ 0% | ⚪ Não iniciado |

**Total Geral:** 3/80 exercícios (3.75%) | 0/17 projetos (0%)

📍 **Ver detalhes:** [`tracker.md`](docs/diario-de-aprendizado/tracker.md)

---

## 🚀 Início Rápido

**Nunca programou microcontroladores?** Siga estes passos:

1. 🗺️ Consulte [`roadmap_geral.md`](docs/roadmaps/roadmap_geral.md) para o plano completo
2. ⚙️ Configure seu ambiente em [`j1-configuracao-ambiente.md`](docs/ferramentas/j1-configuracao-ambiente.md)
3. 💡 Faça seu primeiro projeto em [`mcu/i0-arduino/j1-exercicios/nivel-1-basico/k1-blink_led/`](mcu/i0-arduino/j1-exercicios/nivel-1-basico/k1-blink_led/)

## 📂 Estrutura do Repositório

```
mc_journey_attempt/
│
├── README.md                   # 👈 Você está aqui (apresentação + índice)
│
├── docs/                        # 📚 Documentação de aprendizado
│   ├── README.md                # Navegação da pasta learn/
│   ├── roadmaps/                # Roadmaps completos (40-50 semanas)
│   ├── conceitos-fundamentais/  # GPIO, PWM, I2C, SPI, etc
│   ├── ferramentas/             # Setup, datasheets, debugging
│   ├── diario-aprendizado/      # Diário pessoal de progresso
│   ├── templates/               # Templates para exercícios/projetos
│   └── referencias/             # Referências organizadas por tipo
│
├── mcu/                         # 💻 Código para cada microcontrolador
│   ├── README.md                # Navegação e ordem de estudo
│   ├── i0-arduino/              # Arduino (relembrar básicos)
│   ├── i1-esp32/                # ESP32 (WiFi/Bluetooth)
│   ├── i2-rp2040-a/             # RP2040 (PIO, dual-core)
│   ├── i3-rp2040-zero/          # RP2040 Zero (compacto)
│   └── i4-stm8/                 # STM8 (bare metal)
│
└── projetos-integrados/        # 🔗 Projetos multi-MCU
    └── README.md 

```

## 📖 Sistema de Navegação

Cada pasta contém um arquivo `README.md` ou `index.md` com:
- **Índice/navegação** no topo
- Descrição do conteúdo
- Estrutura interna
- Como usar
- Próximos passos

### Convenção de Nomes

- **Pastas principais:** prefixo `iN-` (i0, i1, i2, ...) para índice de diretórios
- **Arquivos:** prefixo `jN-` (j1, j2, j3, ...) para arquivos dentro de `iN/`
- **Subpastas de exercícios:** prefixo `kN-` (k1, k2, k3, ...) para pastas dentro de exercícios
- **Datas:** formato ISO `dia-YYYY-MM-DD` (ex: `dia-2025-12-25.md`)

## 📚 Sobre o Projeto

Este é um repositório de aprendizado pessoal que documenta minha jornada estudando microcontroladores do zero, com o objetivo de:

- 🎓 **Aprender** conceitos desde o básico até bare metal
- 📝 **Documentar** cada passo para consulta futura
- 🤝 **Compartilhar** conhecimento com outros iniciantes
- 🛠️ **Criar** projetos reais em áreas como robótica, wearables, IoT, automação

## 🎯 Objetivos

1. **Aprender** microcontroladores do zero
2. **Documentar** tudo para futuro (meu e de outros)
3. **Progredir** de forma estruturada (4h/semana)
4. **Dominar** conceitos bare metal e registradores
5. **Criar** projetos reais (robótica, wearables, IoT, etc)

## 🗂️ Estrutura

O repositório está organizado em:

- **`docs/`** - Documentação teórica, roadmap, diário de aprendizado
- **`mcu/`** - Código e projetos para cada microcontrolador (Arduino, ESP32, RP2040, STM8)
- **`projetos-integrados/`** - Projetos que usam múltiplos MCUs

## 🛠️ Hardware Disponível

- **Arduino UNO** - Relembrar conceitos
- **ESP32 (38 pinos)** - WiFi/Bluetooth, dual-core
- **RP2040-A** - PIO, dual-core ARM
- **RP2040 Zero** - Versão compacta
- **STM8** - 8-bit, bare metal

## 🔗 Links Rápidos

| Recurso | Link |
|---------|------|
| 🗺️ Roadmap Completo | [`roadmap_geral.md`](docs/roadmaps/roadmap_geral.md) |
| 📚 Referências | [`referencias/`](docs/referencias/index.md) |
| 📝 Templates | [`templates.md`](docs/templates/index.md) |
| 💻 Primeiro Exercício | [`blink_led/`](mcu/i0-arduino/j1-exercicios/nivel-1-basico/k1-blink_led/) |
| 📊 Diário de Progresso | [`diario-de-aprendizado/`](docs/diario-de-aprendizado/index.md) |
| 📖 Aprendizado | [`docs/`](docs/index.md) |
| 💻 Microcontroladores | [`mcu/`](mcu/README.md) |
| 🔗 Projetos Integrados | [`projetos-integrados/`](projetos-integrados/readme.md) |

## 📈 Progresso

- ✅ Fase 0: Preparação e estruturação do repositório
- 🔄 Fase 1: Fundamentos com Arduino/ESP32
- ⏳ Fase 2-6: Em planejamento

Acompanhe o progresso detalhado em [`diario-de-aprendizado/`](docs/diario-de-aprendizado/)

## 🤝 Contribuições

Este é um repositório de aprendizado pessoal, mas sugestões e correções são bem-vindas via Issues!

---

**Autor:** [@gatilhoroxo](https://github.com/gatilhoroxo)  
**Última atualização:** 2026-02-04


