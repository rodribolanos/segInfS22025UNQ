
CC      := gcc
CFLAGS  := -Wall -Wextra -std=c11 -MMD -MP
DEBUG_FLAGS := -g -O0 -DDEBUG

SRC_DIR := src
BUILD   := build

SRC     := $(SRC_DIR)/main.c \
           $(SRC_DIR)/array_rotation.c \
           $(SRC_DIR)/aes_utils.c

OBJ     := $(SRC:$(SRC_DIR)/%.c=$(BUILD)/%.o)
DEPS    := $(OBJ:.o=.d)

TARGET  := aes

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/%.o: $(SRC_DIR)/%.c | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

debug: CFLAGS += $(DEBUG_FLAGS)
debug: clean $(TARGET)x

clean:
	rm -rf $(BUILD) $(TARGET)

-include $(DEPS)

.PHONY: all clean debug
