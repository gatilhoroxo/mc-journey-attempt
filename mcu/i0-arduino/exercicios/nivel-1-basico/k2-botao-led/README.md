# k2-botao-led/

Exercício 2: Controlar LED com botão

---

## 📑 Índice

1. [🎯 Objetivo](#-objetivo)
2. [📦 Componentes](#-componentes)
3. [🔌 Conexão](#-conexão)
4. [💻 Arquivos](#-arquivos)
5. [📚 Conceitos](#-conceitos)
6. [🚀 Desafios](#-desafios)

---

## 🎯 Objetivo

Ler estado de um botão e controlar LED (acender/apagar).

## 📦 Componentes

- Arduino UNO
- 1x LED
- 1x Resistor 220Ω
- 1x Botão (push button)
- 1x Resistor 10kΩ (pull-down)
- Jumpers

## 🔌 Conexão

```
Arduino Pin 9 → Resistor 220Ω → LED → GND
Arduino Pin 2 → Botão → 5V
Arduino Pin 2 → Resistor 10kΩ → GND (pull-down)
```

**Alternativa (usando pull-up interno):**
```
Arduino Pin 2 → Botão → GND
(usar INPUT_PULLUP no código)
```

## 💻 Arquivos

| Arquivo | Descrição |
|---------|-----------|
| [`leds_com_botao.ino`](leds_com_botao.ino) | Código principal |

## 📚 Conceitos

- `digitalRead()` - Ler estado digital (HIGH/LOW)
- **Pull-down resistor** - Evitar flutuação de sinal
- **Debouncing** (software) - Eliminar ruído do botão
- Lógica de **toggle** - Alternar estado

## 🚀 Desafios

1. Implementar debouncing por software (delay de 50ms)
2. Fazer LED piscar enquanto botão está pressionado
3. Contar e exibir número de cliques no Serial Monitor
4. Usar 2 botões para controlar 2 LEDs independentes

---

**Voltar:** [`../README.md`](../README.md)
