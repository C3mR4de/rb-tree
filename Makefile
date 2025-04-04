BUILD_DIR = build
SOURCE_DIR = src
CC = gcc

TARGET = c_multithreading
PREFIX = /usr/local/bin
CFLAGS = -std=c23 -Wall -Wextra -Wpedantic

.PHONY: all clean install uninstall

all: $(BUILD_DIR)/$(TARGET)

clean:
	rm -rf $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/$(TARGET): $(SOURCE_DIR)/main.c
	mkdir $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SOURCE_DIR)/main.c -o $(BUILD_DIR)/$(TARGET)

install:
	install $(BUILD_DIR)/$(TARGET) $(PREFIX)

uninstall:
	rm -rf $(PREFIX)/$(TARGET)

