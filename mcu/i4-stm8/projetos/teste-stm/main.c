// main.c
#include <stdint.h>

// ========================================
// REGISTRADORES DO STM8S103F3
// ========================================

// Clock Control Register (CLK)
#define CLK_DIVR   (*(volatile uint8_t *)0x50C6)
#define CLK_PCKENR1 (*(volatile uint8_t *)0x50C7)

// Port B Registers (LED normalmente em PB5)
#define PB_ODR  (*(volatile uint8_t *)0x5005)  // Output Data Register
#define PB_IDR  (*(volatile uint8_t *)0x5006)  // Input Data Register
#define PB_DDR  (*(volatile uint8_t *)0x5007)  // Data Direction Register
#define PB_CR1  (*(volatile uint8_t *)0x5008)  // Control Register 1
#define PB_CR2  (*(volatile uint8_t *)0x5009)  // Control Register 2

// ========================================
// DELAY SIMPLES (BLOQUEANTE)
// ========================================
void delay_ms(uint16_t ms) {
    uint16_t i;
    uint8_t j;
    
    for(i = 0; i < ms; i++) {
        for(j = 0; j < 120; j++) {
            // Loop vazio para delay
            // ~1ms a 16MHz (aproximado)
        }
    }
}

// ========================================
// FUNÇÃO PRINCIPAL
// ========================================
void main(void) {
    // 1. Configurar Clock
    CLK_DIVR = 0x00;  // Sem divisão = 16MHz
    
    // 2. Configurar PB5 como saída (LED)
    PB_DDR |= (1 << 5);   // 1 = Output, 0 = Input
    PB_CR1 |= (1 << 5);   // 1 = Push-pull, 0 = Pseudo open-drain
    PB_CR2 &= ~(1 << 5);  // 0 = Até 2MHz, 1 = Até 10MHz
    
    // 3. Loop infinito
    while(1) {
        PB_ODR |= (1 << 5);   // Liga LED (bit 5 = 1)
        delay_ms(1000);
        
        PB_ODR &= ~(1 << 5);  // Desliga LED (bit 5 = 0)
        delay_ms(1000);
    }
}