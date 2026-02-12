# Configurações
CC = sdcc
CFLAGS = -mstm8 --std-sdcc99 --opt-code-size
BUILD = build
TARGET = main
MCU = stm8s103f3

# Compilação
all: $(BUILD)/$(TARGET).ihx

$(BUILD)/$(TARGET).ihx: $(TARGET).c
	@mkdir -p $(BUILD)
	$(CC) $(CFLAGS) $(TARGET).c -o $(BUILD)/$(TARGET).ihx

# Gravação
flash: $(BUILD)/$(TARGET).ihx
	stm8flash -c stlinkv2 -p $(MCU) -w $(BUILD)/$(TARGET).ihx

# Limpeza
clean:
	rm -rf $(BUILD)
	rm -f *.asm *.lst *.rel *.rst *.sym *.ihx *.lk *.map *.mem

.PHONY: all flash clean