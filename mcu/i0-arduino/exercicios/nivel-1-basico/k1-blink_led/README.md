# k1-blink_led/

Exercício 1: Piscar LED

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

Aprender a controlar um LED usando GPIO digital.

## 📦 Componentes

- Arduino UNO
- 1x LED
- 1x Resistor 220Ω
- Jumpers

## 🔌 Conexão

```
Arduino Pin 9 → Resistor 220Ω → LED (ânodo +)
LED (cátodo -) → GND
```

## 💻 Arquivos

| Arquivo | Descrição |
|---------|-----------|
| [`basic.ino`](basic.ino) | Versão básica com `delay()` |
| [`better.ino`](better.ino) | Versão melhorada com `millis()` |

## 📚 Conceitos

- `pinMode()` - Configurar pino como saída
- `digitalWrite()` - Escrever HIGH/LOW
- `delay()` vs `millis()` - Blocking vs non-blocking

## 🚀 Desafios

1. Fazer piscar 2 LEDs alternadamente
2. Criar padrão SOS em código Morse (... --- ...)
3. Controlar velocidade de piscar com potenciômetro

---

**Voltar:** [`../README.md`](../README.md)
