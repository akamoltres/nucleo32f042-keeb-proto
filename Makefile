CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
CFLAGS = -mthumb -g
LDFLAGS = -nostdlib

BUILD_DIR = build

SRC := $(shell find src -name "*.c")
OBJ := $(addprefix $(BUILD_DIR)/,$(addsuffix .o,$(SRC)))
INCLUDES = -Iinclude/
SECTIONS := sections.ld

# default
all: proto

builddir:
	@ mkdir -p $(BUILD_DIR)

clean:
	@ rm -rf $(BUILD_DIR)

build/%.o: %
	@ mkdir -p $(dir $@)
	@ $(CC) $< -c $(CFLAGS) $(INCLUDES) -o $@

.PHONY: proto
proto: proto.elf
proto.elf: $(SECTIONS) $(OBJ)
	@ $(CC) -Wl,-Map=$(BUILD_DIR)/$(addsuffix .map,$(basename $@)) -T$(SECTIONS) $(OBJ) $(LDFLAGS) -o $(BUILD_DIR)/$@
	@ $(OBJCOPY) -O binary $(BUILD_DIR)/$@ $(BUILD_DIR)/$(addsuffix .bin,$(basename $@))
