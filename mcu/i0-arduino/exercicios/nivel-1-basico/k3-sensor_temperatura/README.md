# k3-sensor_temperatura/

Exercício 3: Ler sensor de temperatura

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

Ler valores analógicos de um sensor e converter para temperatura.

## 📦 Componentes

- Arduino UNO
- 1x Sensor de temperatura (LM35 ou TMP36)
- Jumpers

## 🔌 Conexão

```
Sensor VCC → Arduino 5V
Sensor GND → Arduino GND
Sensor OUT → Arduino Pin A0
```

## 💻 Arquivos

| Arquivo | Descrição |
|---------|-----------|
| [`basic.ino`](basic.ino) | Leitura básica e conversão |
| [`better.ino`](better.ino) | Com média móvel e Serial |

## 📚 Conceitos

- `analogRead()` - Leitura ADC (0-1023)
- **Conversão ADC → Voltagem**: `V = (ADC * 5.0) / 1024.0`
- **Conversão Voltagem → Temperatura** (depende do sensor):
  - **LM35**: `T(°C) = V * 100`
  - **TMP36**: `T(°C) = (V - 0.5) * 100`
- `Serial.print()` para debug
- **Média móvel** (filtro digital)

## 🚀 Desafios

1. Mostrar temperatura em display LCD I2C
2. Ligar LED se temperatura > threshold (ex: 25°C)
3. Enviar dados formatados para computador (CSV)
4. Calcular e exibir temperatura mín/máx/média
5. Criar gráfico em tempo real (Processing ou Python)

---

**Voltar:** [`../README.md`](../README.md)
