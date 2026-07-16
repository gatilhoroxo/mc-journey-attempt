# Exercício 24: Otimização de Performance

## 📖 Descrição

Comparação de diferentes técnicas de otimização em Arduino:
- digitalWrite vs registradores diretos
- Funções normais vs inline vs macros
- Cálculo vs lookup tables
- Strings em RAM vs PROGMEM
- Memory alignment

## 🎯 Objetivos

1. Medir diferenças de performance
2. Entender trade-offs (velocidade vs memória)
3. Aplicar otimizações apropriadas
4. Analisar uso de memória

## 🔧 Hardware

- Arduino UNO
- Cabo USB
- (Opcional: LED externo)

## 📊 Resultados Esperados

```
digitalWrite:        ~600 us
Direct Port:         ~25 us
Speedup:             ~24x

Normal function:     ~200 us
Inline function:     ~50 us
Macro:               ~50 us

sin() calculation:   ~8000 us
Lookup table:        ~300 us
Speedup:             ~27x
```

## 💡 Conceitos

- **Registradores:** Acesso direto ao hardware
- **Inline:** Elimina overhead de chamada de função
- **Lookup Tables:** Troca cálculo por memória
- **PROGMEM:** Salva constantes na Flash
- **Memory Alignment:** Organização eficiente na memória

## 🚀 Como Usar

1. Abra `performance_test.ino` no Arduino IDE
2. Faça upload para Arduino UNO
3. Abra Serial Monitor (115200 baud)
4. Observe os resultados dos testes

## 📝 Análise

### Quando usar Registradores?
- ✅ Controle de múltiplos pinos simultaneamente
- ✅ Loops críticos de timing
- ✅ Comunicação bit-banging
- ❌ Código portável entre placas

### Quando usar Lookup Tables?
- ✅ Funções matemáticas complexas (sin, cos, exp)
- ✅ Conversões frequentes
- ✅ MCU tem Flash sobrando, RAM limitada
- ❌ Valores muito variáveis ou alta precisão necessária

### Quando usar PROGMEM?
- ✅ Strings de texto fixo
- ✅ Tabelas de dados grandes
- ✅ RAM escassa (< 500 bytes livres)
- ❌ Dados acessados muito frequentemente

## 🔗 Referências

- [AVR Optimization Guide](https://www.nongnu.org/avr-libc/user-manual/optimization.html)
- [ATmega328P Datasheet](https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf)
