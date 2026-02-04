# i3-rp2040-zero/

RP2040 Zero - Versão compacta para projetos wearables.

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
i3-rp2040-zero/
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

Otimizar código para hardware compacto, ideal para wearables e projetos com espaço limitado.

**Por que RP2040 Zero?**
- Mesmo chip do RP2040-A
- Form factor ultra-compacto
- Perfeito para wearables
- Menos pinos = design mais simples
- Baixo consumo de energia

**Foco:**
- Otimização de código
- Gerenciamento de energia
- Projetos vestíveis

## 🔧 Setup

### Hardware Necessário
- RP2040 Zero
- Cabo USB-C
- Protoboard ou PCB customizado
- Componentes SMD (opcionalmente)

### Software
- Mesmo do RP2040-A (Pico SDK)
- Foco em otimização e low-power

## 📚 Conteúdo por Nível

### Nível 1 - Básico
- GPIO limitado
- PWM
- I2C/SPI (sensores compactos)
- Sleep modes

### Nível 2 - Intermediário
- Power management
- Bateria e carregamento
- Displays pequenos (OLED)
- Sensores de movimento (IMU)

### Nível 3 - Avançado
- Deep sleep optimization
- Wearable projects
- PCB design
- Case design (3D printing)

## 🔗 Próximo Passo

Após completar o **Nível 2** aqui, siga para:
- **[../i4-stm8/](../i4-stm8/)** - Bare metal 8-bit

Ou consulte:
- **Projetos integrados:** [`../../projetos-integrados/`](../../projetos-integrados/)
- **Roadmap geral:** [`roadmap_geral.md`](../../docs/roadmaps/roadmap_geral.md)
- **Referências:** [`REFERENCIAS.md`](../../docs/referencias/REFERENCIAS.md)
- **Voltar:** [`README.md`](../README.md)

---

**Status atual:** Em planejamento

**Pré-requisito:** Completar RP2040-A Nível 2
