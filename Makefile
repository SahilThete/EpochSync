###############################################################################
# EpochSync
# Makefile
#
# PS2SDK Build System
###############################################################################

#------------------------------------------------------------------------------
# Project
#------------------------------------------------------------------------------

EE_BIN		:= EpochSync

#------------------------------------------------------------------------------
# Environment Checks
#------------------------------------------------------------------------------

ifndef PS2DEV
$(error PS2DEV environment variable is not defined)
endif

ifndef PS2SDK
$(error PS2SDK environment variable is not defined)
endif

#------------------------------------------------------------------------------
# Toolchain
#------------------------------------------------------------------------------

CROSS		:= mips64r5900el-ps2-elf
EE_CC		:= $(CROSS)-gcc
EE_CXX		:= $(CROSS)-g++
EE_AS		:= $(CROSS)-as
EE_SIZE		:= $(CROSS)-size
EE_STRIP	:= $(CROSS)-strip
EE_OBJDUMP	:= $(CROSS)-objdump
EE_READELF	:= $(CROSS)-readelf

#------------------------------------------------------------------------------
# Source Directories
#------------------------------------------------------------------------------

SRC_DIRS := \
	src \
	src/core \
	src/common \
	src/config \
	src/launcher \
	src/network \
	src/ntp \
	src/rtc \
	src/system \
	src/ui

#------------------------------------------------------------------------------
# Source Files
#------------------------------------------------------------------------------

EE_SRCS :=

EE_SRCS += $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))

EE_OBJS := $(EE_SRCS:.c=.o)

EE_DEPENDS := $(EE_OBJS:.o=.d)

#------------------------------------------------------------------------------
# Include Directories
#------------------------------------------------------------------------------

EE_INCS := \
	-I. \
	-Isrc \
	-Isrc/core \
	-Isrc/common \
	-Isrc/config \
	-Isrc/launcher \
	-Isrc/network \
	-Isrc/ntp \
	-Isrc/rtc \
	-Isrc/system \
	-Isrc/ui \
	-I$(PS2SDK)/common/include \
	-I$(PS2SDK)/ee/include \
	-I$(PS2DEV)/gsKit/include

#------------------------------------------------------------------------------
# Libraries
#------------------------------------------------------------------------------

EE_LIBS := \
	-lkernel \
	-lc \
	-lpatches

#------------------------------------------------------------------------------
# Compiler Flags
#------------------------------------------------------------------------------

DEBUG ?= 0

EE_CFLAGS := \
	-D_EE \
	-G0 \
	-Wall \
	-Wextra \
	-Wshadow \
	-Wpointer-arith \
	-Wmissing-prototypes \
	-Wstrict-prototypes \
	-Wundef \
	-Werror=implicit-function-declaration \
	-ffunction-sections \
	-fdata-sections \
	-MMD \
	-MP

ifeq ($(DEBUG),1)

EE_CFLAGS += -O0 -g -DDEBUG

else

EE_CFLAGS += -O2

endif

EE_CXXFLAGS := $(EE_CFLAGS)

#------------------------------------------------------------------------------
# Linker Flags
#------------------------------------------------------------------------------

EE_LDFLAGS := \
	-Wl,--gc-sections \
	-Wl,-Map,$(EE_BIN).map \
	-L$(PS2SDK)/ee/lib

#------------------------------------------------------------------------------
# Default Target
#------------------------------------------------------------------------------

all: $(EE_BIN).elf

#------------------------------------------------------------------------------
# Linking
#------------------------------------------------------------------------------

$(EE_BIN).elf: $(EE_OBJS)

	$(EE_CC) \
	$(EE_OBJS) \
	$(EE_LDFLAGS) \
	$(EE_LIBS) \
	-o $@

	@echo
	@echo "========================================"
	@echo "EpochSync Build Complete"
	@echo "========================================"
	@$(EE_SIZE) $(EE_BIN).elf
	@echo

#------------------------------------------------------------------------------
# Compile C
#------------------------------------------------------------------------------

%.o: %.c

	$(EE_CC) \
	$(EE_CFLAGS) \
	$(EE_INCS) \
	-c $< \
	-o $@

#------------------------------------------------------------------------------
# Dependency Files
#------------------------------------------------------------------------------

-include $(EE_DEPENDS)

#------------------------------------------------------------------------------
# Utilities
#------------------------------------------------------------------------------

clean:

	rm -f $(EE_OBJS)
	rm -f $(EE_DEPENDS)
	rm -f $(EE_BIN).elf
	rm -f $(EE_BIN).map
	rm -f $(EE_BIN).disasm
	rm -f $(EE_BIN).sym
	rm -f $(EE_BIN).lst

	@echo "Build artifacts removed."

rebuild: clean all

debug:

	$(MAKE) DEBUG=1

release:

	$(MAKE) clean

	$(MAKE) DEBUG=0

	$(EE_STRIP) $(EE_BIN).elf

	@echo
	@echo "Release build generated."

size:
	$(EE_SIZE) $(EE_BIN).elf

info:
	$(EE_READELF) -h $(EE_BIN).elf

sections:
	$(EE_READELF) -S $(EE_BIN).elf

symbols:
	$(EE_READELF) -s $(EE_BIN).elf

disasm:
	$(EE_OBJDUMP) -d $(EE_BIN).elf

run:

	@echo "Copy EpochSync.elf to your PS2 device."

#------------------------------------------------------------------------------
# EOF
#------------------------------------------------------------------------------