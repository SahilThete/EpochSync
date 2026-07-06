# Makefile for EpochSync NTP client for PS2
# Uses absolute PS2SDK toolchain paths and builds nested source directories.

TARGET := EpochSync
SRCDIR := src
BUILDDIR := build
BINDIR := bin

PS2DEV ?= $(PS2DEV)
EE_BIN = $(PS2DEV)/ee/bin
CC := $(EE_BIN)/mips64r5900el-ps2-elf-gcc.exe
LD := $(CC)
OBJCOPY := $(EE_BIN)/mips64r5900el-ps2-elf-objcopy.exe
CFLAGS := -O2 -G0 -Wall -fno-builtin -mno-abicalls -ffreestanding -I$(SRCDIR)
LDFLAGS := -Tlinkfile.ld -nostdlib

SRCS := main.c $(wildcard $(SRCDIR)/*/*.c)
OBJS := $(patsubst %.c,$(BUILDDIR)/%.o,$(SRCS))

ELF := $(BINDIR)/$(TARGET).elf
BIN := $(BINDIR)/$(TARGET).bin

.PHONY: all clean dirs install

all: dirs $(BIN)

dirs:
	@mkdir -p $(sort $(dir $(OBJS))) $(BINDIR)

$(BUILDDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(ELF): $(OBJS)
	$(LD) $(LDFLAGS) $^ -o $@

$(BIN): $(ELF)
	$(OBJCOPY) -O binary $< $@

clean:
	-rm -f $(OBJS) $(ELF) $(BIN)

install: all
	@echo "Build complete. Copy $(BIN) to your PS2 or package as needed."

# EOF
