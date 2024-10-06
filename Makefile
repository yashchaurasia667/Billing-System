CC=gcc
CFLAGS=-Wall
BUILD_DIR=build

default: main

all: $(BUILD_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

main: $(BUILD_DIR) main.c
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/main main.c
	$(BUILD_DIR)/main

clean:
	rm -rf $(BUILD_DIR)