XC8 ?= /home/nadn20/.local/microchip/xc8/v3.10/bin/xc8-cc
DEVICE ?= 18F46K22
MDFP ?= /home/nadn20/.mchp_packs/Microchip/PIC18F-K_DFP/1.13.292/extracted/xc8
BUILD_DIR ?= build
TARGET ?= elevator.production

SOURCES := \
	firmware/src/app/elevator_control.c \
	firmware/src/app/elevator_state_machine.c \
	firmware/src/app/main.c \
	firmware/src/bsp/input_config.c \
	firmware/src/bsp/output_config.c \
	firmware/src/platform/eusart1.c \
	firmware/src/platform/interrupt_manager.c \
	firmware/src/platform/mcc.c \
	firmware/src/platform/system_init.c

INCLUDES := -Ifirmware/include

OUTPUT_ELF := $(BUILD_DIR)/$(TARGET).elf
OUTPUT_HEX := $(BUILD_DIR)/$(TARGET).hex

.PHONY: all compile clean print-config

all: compile

compile: $(OUTPUT_ELF)

$(OUTPUT_ELF): $(SOURCES) | $(BUILD_DIR)
	$(XC8) -mcpu=$(DEVICE) -mdfp=$(MDFP) $(INCLUDES) $(SOURCES) -o $(OUTPUT_ELF)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

print-config:
	@echo "XC8=$(XC8)"
	@echo "DEVICE=$(DEVICE)"
	@echo "MDFP=$(MDFP)"
	@echo "OUTPUT_ELF=$(OUTPUT_ELF)"
	@echo "OUTPUT_HEX=$(OUTPUT_HEX)"
