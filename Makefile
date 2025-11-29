# Compiler and flags
CC      := gcc
CFLAGS  := -Wall -Wextra -std=c11 -MMD -MP
DEBUG_FLAGS := -g -O0 -DDEBUG

# Directories
SRC_DIR := src
BUILD   := build

# Source files (inside src/)
SRC     := $(SRC_DIR)/main.c \
           $(SRC_DIR)/array_rotation.c \
           $(SRC_DIR)/aes_utils.c

# Object files in build/
OBJ     := $(SRC:$(SRC_DIR)/%.c=$(BUILD)/%.o)
DEPS    := $(OBJ:.o=.d)

# Executable at root
TARGET  := aes

# Default rule
all: $(TARGET)

# Link executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Ensure build folder exists
$(BUILD):
	mkdir -p $(BUILD)

# Compile .c → build/*.o
$(BUILD)/%.o: $(SRC_DIR)/%.c | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

# Debug build
debug: CFLAGS += $(DEBUG_FLAGS)
debug: clean $(TARGET)
	@echo "Compiled with debug flags."

# Cleanup
clean:
	rm -rf $(BUILD) $(TARGET)

# Include auto-generated dependency files
-include $(DEPS)

.PHONY: all clean debug
