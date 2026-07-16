# 💻 mcu/

Código e projetos para cada microcontrolador.

---

## 📑 Índice

1. [📂 Estrutura](#-estrutura)
2. [🎯 Ordem de Estudo Sugerida](#-ordem-de-estudo-sugerida)
3. [📝 Estrutura Interna de Cada MCU](#-estrutura-interna-de-cada-mcu)
4. [🔗 Links Relacionados](#-links-relacionados)

---

## 📂 Estrutura

```
mcu/
├── README.md             # 👈 Navegação (você está aqui)
├── i0-arduino/           # Arduino (framework conhecido)
│   └── README.md
├── i1-esp32/             # ESP32 (WiFi/Bluetooth, dual-core)
│   └── README.md
├── i2-rp2040-a/          # RP2040 (PIO, dual-core ARM)
│   └── README.md
├── i3-rp2040-zero/       # RP2040 Zero (versão compacta)
│   └── README.md
└── i4-stm8/              # STM8 (8-bit, bare metal)
    └── README.md
```

## 🎯 Ordem de Estudo Sugerida

1. **[i0-arduino/](i0-arduino/)** - Relembrar conceitos básicos com framework familiar
2. **[i1-esp32/](i1-esp32/)** - Fundamentos com recursos modernos (WiFi, dual-core)
3. **[i2-rp2040-a/](i2-rp2040-a/)** - Aprofundar em arquitetura ARM e PIO
4. **[i3-rp2040-zero/](i3-rp2040-zero/)** - Otimização para hardware limitado
5. **[i4-stm8/](i4-stm8/)** - Bare metal e registradores

## 📝 Estrutura Interna de Cada MCU

Cada pasta `iN-[mcu]/` contém:

```
iN-mcu/
├── README.md              # Info + roadmap específico do MCU
├── j1-exercicios/         # Exercícios progressivos
│   ├── nivel-1-basico/
│   ├── nivel-2-intermediario/
│   └── nivel-3-avancado/
└── j2-projetos/           # Projetos completos
```

### Níveis de Exercícios

- **Nível 1 (Básico):** GPIO, PWM, Serial, ADC
- **Nível 2 (Intermediário):** Interrupts, I2C, SPI, Timers
- **Nível 3 (Avançado):** RTOS, DMA, otimizações, bare metal

## 🔗 Links Relacionados

- **Roadmap geral:** [`roadmap_geral.md`](../docs/roadmaps/roadmap_geral.md)
- **Referências:** [`REFERENCIAS.md`](../docs/referencias/REFERENCIAS.md)
- **Projetos multi-MCU:** [`projetos-integrados/`](../projetos-integrados/)
- **Templates:** [`templates/`](../docs/templates/)
- **Voltar:** [`README.md`](../README.md)

---

**Dica:** Comece pelo Arduino mesmo que já tenha experiência - é útil para estabelecer uma base sólida!
