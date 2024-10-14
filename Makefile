CC = gcc
AR = ar

BUILD_DIR = ./build

LIB_SOURCES = $(wildcard ./source/*.c)
LIB_HEADERS = $(wildcard ./source/*.h)
LIB_OBJECTS = $(patsubst ./source/%.c, $(BUILD_DIR)/%.o, $(LIB_SOURCES))

LIB_TARGET = $(BUILD_DIR)/libtermui.a

INC_PATH = /usr/local/include/TERMUI

all: $(LIB_TARGET) examples

lib: $(LIB_TARGET)

install: $(LIB_TARGET)
	@echo 'Note: This installation helper must be run with root privileges.'
	@echo 'Note: This installation helper only copies the header files to "$(INC_PATH)".'
	@echo 'To compile your project, you need to link "$(LIB_TARGET)" just the same as you do with your objects files.'
	mkdir -p $(INC_PATH)
	cp -v $(LIB_HEADERS) $(INC_PATH)

uninstall:
	rm -rf $(INC_PATH)

examples: helloworld.o | $(LIB_TARGET)
	$(CC) -Wall -Wextra -o $(BUILD_DIR)/helloworld $(BUILD_DIR)/$< -Lbuild -ltermui

helloworld.o: $(BUILD_DIR)
	$(CC) -c ./tests/helloworld.c -o $(BUILD_DIR)/$@

$(BUILD_DIR):
	mkdir -p $@

$(LIB_TARGET): $(LIB_OBJECTS) | $(BUILD_DIR)
	$(AR) rcs $@ $^

$(BUILD_DIR)/%.o: ./source/%.c $(LIB_HEADERS) | $(BUILD_DIR)
	$(CC) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all install clean
