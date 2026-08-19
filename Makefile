# This Makefile was generated with AI because old one is not working with arm11 code and i'm too lazy to make new one, you can call this vibe-coded (Makefile only)

ifeq ($(strip $(DEVKITARM)),)
$(error DEVKITARM is not set)
endif

include $(DEVKITARM)/ds_rules

PROJECT := $(CURDIR)

OUTPUT := $(PROJECT)/output
BUILD  := $(PROJECT)/build

CC      := $(DEVKITARM)/bin/arm-none-eabi-gcc
LD      := $(DEVKITARM)/bin/arm-none-eabi-gcc
AS      := $(DEVKITARM)/bin/arm-none-eabi-gcc
OBJCOPY := $(DEVKITARM)/bin/arm-none-eabi-objcopy

# =============================================================================
# Common flags
# =============================================================================

COMMON_CFLAGS := \
	-g \
	-Wall \
	-Wextra \
	-Wpedantic \
	-Wcast-align \
	-Wno-main \
	-O2 \
	-fomit-frame-pointer \
	-ffast-math \
	-std=gnu11 \
	-fno-builtin-memcpy \
	-fdata-sections \
	-ffunction-sections

COMMON_INCLUDES := \
	-I$(PROJECT)/source \
	-I$(PROJECT)/source/common \
	-I$(PROJECT)/source/common/hardware \
	-I$(PROJECT)/source/common/input \
	-I$(PROJECT)/source/common/ui \
	-I$(PROJECT)/source/font \
	-I$(PROJECT)/source/crypto \
	-I$(PROJECT)/source/fatfs \
	-I$(PROJECT)/source/nand \
	-I$(PROJECT)/source/safety \
	-I$(PROJECT)/source/utils \
	-I$(PROJECT)/source/kernel

# =============================================================================
# ARM9
# =============================================================================

ARM9_CFLAGS := \
	$(COMMON_CFLAGS) \
	$(COMMON_INCLUDES) \
	-march=armv5te \
	-mtune=arm946e-s \
	-mthumb \
	-mthumb-interwork \
	-DARM9

ARM9_ASFLAGS := \
	-g \
	-mcpu=arm946e-s \
	-mthumb \
	-mthumb-interwork

ARM9_LDFLAGS := \
	-T$(PROJECT)/link.ld \
	-nostartfiles \
	-march=armv5te \
	-mtune=arm946e-s \
	-mthumb \
	-mthumb-interwork \
	-Wl,--gc-sections

ARM9_BUILD := $(BUILD)/arm9

ARM9_SOURCES := \
	$(wildcard $(PROJECT)/source/*.c) \
	$(wildcard $(PROJECT)/source/common/*.c) \
	$(wildcard $(PROJECT)/source/common/hardware/*.c) \
	$(wildcard $(PROJECT)/source/common/input/*.c) \
	$(wildcard $(PROJECT)/source/common/ui/*.c) \
	$(wildcard $(PROJECT)/source/crypto/*.c) \
	$(wildcard $(PROJECT)/source/fatfs/*.c) \
	$(wildcard $(PROJECT)/source/nand/*.c) \
	$(wildcard $(PROJECT)/source/safety/*.c) \
	$(wildcard $(PROJECT)/source/utils/*.c) \
	$(wildcard $(PROJECT)/source/kernel/*.c) \
	$(wildcard $(PROJECT)/source/*.s) \
	$(wildcard $(PROJECT)/source/common/*.s) \
	$(wildcard $(PROJECT)/source/common/hardware/*.s) \
	$(wildcard $(PROJECT)/source/nand/*.s)

ARM9_OBJECTS := \
	$(patsubst $(PROJECT)/source/%.c,$(ARM9_BUILD)/%.o,$(filter %.c,$(ARM9_SOURCES))) \
	$(patsubst $(PROJECT)/source/%.s,$(ARM9_BUILD)/%.o,$(filter %.s,$(ARM9_SOURCES)))

ARM9_ELF := $(OUTPUT)/lunix3ds.elf
ARM9_BIN := $(OUTPUT)/lunix3ds.bin

# =============================================================================
# ARM11
# =============================================================================

ARM11_CFLAGS := \
	$(COMMON_CFLAGS) \
	$(COMMON_INCLUDES) \
	-I$(PROJECT)/source/arm11 \
	-mcpu=mpcore \
	-DARM11

ARM11_ASFLAGS := \
	-g \
	-mcpu=mpcore

ARM11_LDFLAGS := \
	-T$(PROJECT)/link_arm11.ld \
	-nostartfiles \
	-mcpu=mpcore \
	-Wl,--gc-sections

ARM11_BUILD := $(BUILD)/arm11

ARM11_SOURCES := \
	$(wildcard $(PROJECT)/source/arm11/*.c) \
	$(wildcard $(PROJECT)/source/arm11/*.s)

ARM11_OBJECTS := \
	$(patsubst $(PROJECT)/source/%.c,$(ARM11_BUILD)/%.o,$(filter %.c,$(ARM11_SOURCES))) \
	$(patsubst $(PROJECT)/source/%.s,$(ARM11_BUILD)/%.o,$(filter %.s,$(ARM11_SOURCES)))

ARM11_ELF := $(OUTPUT)/lunix3ds_arm11.elf
ARM11_BIN := $(OUTPUT)/lunix3ds_arm11.bin

# =============================================================================
# Targets
# =============================================================================

.PHONY: all arm9 arm11 firm clean

all: firm

arm9: $(ARM9_BIN)

arm11: $(ARM11_BIN)

firm: arm9 arm11
	@echo "  FIRM     $(OUTPUT)/lunix3ds.firm"
	@firmtool build $(OUTPUT)/lunix3ds.firm \
		-n 0x23F00000 \
		-e 0x1FF81000 \
		-D $(ARM9_BIN) $(ARM11_BIN) \
		-A 0x23F00000 0x1FF81000 \
		-C NDMA XDMA \
		-i

# =============================================================================
# ARM9 compilation
# =============================================================================

$(ARM9_BUILD)/%.o: $(PROJECT)/source/%.c
	@mkdir -p $(dir $@)
	@echo "  CC ARM9  $<"
	@$(CC) $(ARM9_CFLAGS) -MMD -MP -c $< -o $@

$(ARM9_BUILD)/%.o: $(PROJECT)/source/%.s
	@mkdir -p $(dir $@)
	@echo "  AS ARM9  $<"
	@$(AS) $(ARM9_ASFLAGS) -c $< -o $@

$(ARM9_ELF): $(ARM9_OBJECTS)
	@mkdir -p $(OUTPUT)
	@echo "  LD ARM9  $@"
	@$(LD) $(ARM9_OBJECTS) $(ARM9_LDFLAGS) -o $@

$(ARM9_BIN): $(ARM9_ELF)
	@echo "  BIN ARM9 $@"
	@$(OBJCOPY) \
		--set-section-flags .bss=alloc,load,contents \
		-O binary \
		$< $@

# =============================================================================
# ARM11 compilation
# =============================================================================

$(ARM11_BUILD)/%.o: $(PROJECT)/source/%.c
	@mkdir -p $(dir $@)
	@echo "  CC ARM11 $<"
	@$(CC) $(ARM11_CFLAGS) -MMD -MP -c $< -o $@

$(ARM11_BUILD)/%.o: $(PROJECT)/source/%.s
	@mkdir -p $(dir $@)
	@echo "  AS ARM11 $<"
	@$(AS) $(ARM11_ASFLAGS) -c $< -o $@

$(ARM11_ELF): $(ARM11_OBJECTS)
	@mkdir -p $(OUTPUT)
	@echo "  LD ARM11 $@"
	@$(LD) $(ARM11_OBJECTS) $(ARM11_LDFLAGS) -o $@

$(ARM11_BIN): $(ARM11_ELF)
	@echo "  BIN ARM11 $@"
	@$(OBJCOPY) \
		--set-section-flags .bss=alloc,load,contents \
		-O binary \
		$< $@

# =============================================================================
# Dependencies
# =============================================================================

-include $(ARM9_OBJECTS:.o=.d)
-include $(ARM11_OBJECTS:.o=.d)

# =============================================================================
# Clean
# =============================================================================

clean:
	rm -rf $(BUILD)
	rm -rf $(OUTPUT)
