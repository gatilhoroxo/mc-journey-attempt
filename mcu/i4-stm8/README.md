# i4-stm8/

STM8 - Microcontrolador 8-bit para programação bare metal.

---

## 📑 Índice

1. [📂 Estrutura](#-estrutura)
2. [🎯 Objetivo](#-objetivo)
3. [🔧 Setup](#-setup)
4. [📚 Conteúdo por Nível](#-conteúdo-por-nível)
5. [🔗 Próximo Passo](#-próximo-passo)

---

## 📂 Estrutura

```
i4-stm8/
├── README.md              # 👈 Você está aqui
├── j1-exercicios/         # Exercícios progressivos
│   ├── README.md
│   ├── nivel-1-basico/
│   ├── nivel-2-intermediario/
│   └── nivel-3-avancado/
└── j2-projetos/           # Projetos completos
    └── README.md
```

## 🎯 Objetivo

Dominar programação bare metal e manipulação direta de registradores.

**Por que STM8?**
- Arquitetura 8-bit mais simples
- Perfeito para aprender bare metal
- Datasheet legível e completo
- Baixíssimo custo
- Sem abstrações - tudo é manual
- Excelente para entender hardware

**Foco:**
- Leitura de datasheets
- Manipulação de registradores
- Assembly (opcional)
- Zero dependências de frameworks

## 🔧 Setup

### Hardware Necessário
- STM8S103F3 ou similar
- Programador ST-Link V2
- Protoboard
- Componentes eletrônicos

### Software
- **Compilador:** SDCC (Small Device C Compiler)
- **Programador:** stm8flash
- **Datasheet:** STM8S Reference Manual (obrigatório!)

### Instalação
```bash
# Linux
sudo apt install sdcc stm8flash

# Testar conexão
stm8flash -c stlinkv2 -p stm8s103f3
```

## 📚 Conteúdo por Nível

### Nível 1 - Básico
- Leitura de datasheet
- Configurar clock
- GPIO via registradores
- Blink LED sem framework
- UART básico

### Nível 2 - Intermediário
- Timers (via registradores)
- Interrupts
- ADC
- PWM
- Low-power modes

### Nível 3 - Avançado
- Assembly inline
- Otimização extrema
- Protocolos sem bibliotecas
- Bootloader próprio
- EEPROM manipulation

## 🔗 Próximo Passo

Após completar o **Nível 3** aqui:
- **[../../projetos-integrados/](../../projetos-integrados/)** - Projetos multi-MCU
- Explorar ARM bare metal (STM32)
- Criar seus próprios projetos!

Ou consulte:
- **Roadmap geral:** [`roadmap_geral.md`](../../docs/roadmaps/roadmap_geral.md)
- **Referências:** [`REFERENCIAS.md`](../../docs/referencias/REFERENCIAS.md)
- **Voltar:** [`README.md`](../README.md)

---

**Status atual:** Em planejamento

**Pré-requisito:** Completar RP2040 Zero Nível 2

**Atenção:** Este é o nível mais desafiador! Tenha paciência e leia MUITO o datasheet.
