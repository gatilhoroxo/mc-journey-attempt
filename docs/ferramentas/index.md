---
title: Ferramentas
description: Ferramentas, configurações e técnicas de desenvolvimento.
---

# 🛠️ Ferramentas

Ferramentas, configurações e técnicas de desenvolvimento.

## 📂 Arquivos

- `j1-configuracao-ambiente.md` - Setup de IDE, compiladores, drivers
- `j2-como-ler-datasheets.md` - Técnicas para entender datasheets
- `j3-debugging.md` - Ferramentas e técnicas de debug
- `j4-boas-praticas.md` - Padrões de código e organização

## 🎯 Essencial para iniciantes

Comece por `j1-configuracao-ambiente.md` antes de escrever qualquer código!

## Pinagem

### 📂 Estrutura

Cada MCU possui:
- Diagrama visual ASCII da pinagem
- Link para datasheet oficial
- Tabela de mapeamento de pinos
- Notas sobre pinos especiais

---

### 🔍 Como Usar

1. **Escolha seu MCU** 
2. **Consulte o diagrama** para identificar pinos
3. **Verifique limitações** na seção de notas
4. **Leia o datasheet** para detalhes técnicos

---

### 📝 Convenções

```
[PIN] - Número físico do pino
GPIO# - Número GPIO lógico
PWM - Capaz de PWM
ADC - Capaz de leitura analógica
I2C - SDA/SCL
SPI - MOSI/MISO/SCK/CS
UART - TX/RX
* - Pino especial (boot, strapping, etc)
```

