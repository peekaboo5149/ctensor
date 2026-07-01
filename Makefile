CC := clang

SRC_DIR := src
TEST_DIR := tests
BUILD_DIR := build

TARGET := $(BUILD_DIR)/main

# SOURCES := $(filter-out $(SRC_DIR)/main.c,$(wildcard $(SRC_DIR)/*.c))
SOURCES := $(shell find src -type f -name "*.c" | grep -v "src/main.c")
MAIN := $(SRC_DIR)/main.c
TEST_SOURCES := $(shell find $(TEST_DIR) -type f -name "*.c")

CRITERION_CFLAGS := $(shell pkg-config --cflags criterion)
CRITERION_LIBS := $(shell pkg-config --libs criterion)

CFLAGS := -std=c17 -Wall -Wextra -Wpedantic -O2 -I$(SRC_DIR)

.PHONY: all build run test clean

all: build

build:
	@rm -rf $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) $(SOURCES) $(MAIN) -o $(TARGET)

run:
	@TMP_DIR=$$(mktemp -d); \
	$(CC) $(CFLAGS) $(SOURCES) $(MAIN) -o $$TMP_DIR/main; \
	$$TMP_DIR/main; \
	rm -rf $$TMP_DIR

test:
	@TMP_DIR=$$(mktemp -d); \
	$(CC) \
		$(CFLAGS) \
		$(CRITERION_CFLAGS) \
		$(SOURCES) \
		$(TEST_SOURCES) \
		-o $$TMP_DIR/tests \
		$(CRITERION_LIBS); \
	$$TMP_DIR/tests; \
	rm -rf $$TMP_DIR

clean:
	@rm -rf $(BUILD_DIR)