# Simple STM32F407VETx Makefile for RPi
PROJECT = zoe_stm_test

# Toolchain
CC      = arm-none-eabi-gcc
AS      = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE    = arm-none-eabi-size

# MCU flags
MCU_CFLAGS = -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard

CORE_DIR    = Core
DRIVERS_DIR = Drivers
BUILD_DIR   = build

INCLUDES = \
  -I$(CORE_DIR)/Inc \
  -I$(DRIVERS_DIR)/STM32F4xx_HAL_Driver/Inc \
  -I$(DRIVERS_DIR)/CMSIS/Device/ST/STM32F4xx/Include \
  -I$(DRIVERS_DIR)/CMSIS/Include

# Core sources
C_SOURCES = \
  $(CORE_DIR)/Src/main.c \
  $(CORE_DIR)/Src/stm32f4xx_it.c \
  $(CORE_DIR)/Src/stm32f4xx_hal_msp.c \
  $(CORE_DIR)/Src/system_stm32f4xx.c \
  $(CORE_DIR)/Src/syscalls.c \
  $(CORE_DIR)/Src/sysmem.c

# HAL sources (add more here if your code uses more peripherals)
C_SOURCES += \
  $(DRIVERS_DIR)/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c \
  $(DRIVERS_DIR)/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c \
  $(DRIVERS_DIR)/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c \
  $(DRIVERS_DIR)/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c \
  $(DRIVERS_DIR)/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c \
  $(DRIVERS_DIR)/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c \
  $(DRIVERS_DIR)/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c \
  $(DRIVERS_DIR)/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c \
  $(DRIVERS_DIR)/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c \
  $(DRIVERS_DIR)/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.c \
  $(DRIVERS_DIR)/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c \
  $(DRIVERS_DIR)/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c

ASM_SOURCES = \
  $(CORE_DIR)/Startup/startup_stm32f407vetx.s

# Object names (flattened into build/)
C_OBJS   = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
ASM_OBJS = $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
OBJECTS  = $(C_OBJS) $(ASM_OBJS)

CFLAGS = $(MCU_CFLAGS) -O2 -g3 -ffunction-sections -fdata-sections -Wall \
         -fstack-usage -MMD -MP \
         -DSTM32F407xx \
         $(INCLUDES)

ASFLAGS = $(MCU_CFLAGS) -x assembler-with-cpp

LDSCRIPT = STM32F407VETX_FLASH.ld
LDFLAGS  = $(MCU_CFLAGS) -T$(LDSCRIPT) -Wl,--gc-sections -Wl,-Map=$(BUILD_DIR)/$(PROJECT).map

all: $(BUILD_DIR)/$(PROJECT).elf $(BUILD_DIR)/$(PROJECT).bin

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Pattern rules for C sources
$(BUILD_DIR)/%.o: $(CORE_DIR)/Src/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(DRIVERS_DIR)/STM32F4xx_HAL_Driver/Src/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Assembler
$(BUILD_DIR)/%.o: $(CORE_DIR)/Startup/%.s | $(BUILD_DIR)
	$(AS) $(ASFLAGS) -c $< -o $@

# Link
$(BUILD_DIR)/$(PROJECT).elf: $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SIZE) $@

# ELF -> BIN
$(BUILD_DIR)/$(PROJECT).bin: $(BUILD_DIR)/$(PROJECT).elf
	$(OBJCOPY) -O binary $< $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
