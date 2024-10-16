RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
RESET = \033[0m

CC = gcc
AR = ar

BUILD_DIR = ./build

LIB_SOURCES = $(wildcard ./source/*.c)
LIB_HEADERS = $(wildcard ./source/*.h)
LIB_OBJECTS = $(patsubst ./source/%.c, $(BUILD_DIR)/%.o, $(LIB_SOURCES))

LIB_TARGET = $(BUILD_DIR)/libtermui.a

INC_PATH = /usr/local/include/TERMUI

all: $(LIB_TARGET) examples

info:
	@echo -e "$(YELLOW) C Compiler:$(RESET) $(GREEN)$(CC) $(RESET)"
	@echo -e "$(YELLOW) Archiver:$(RESET) $(GREEN)$(AR) $(RESET)"

lib: $(LIB_TARGET)

install: $(LIB_TARGET)
	@echo -e 'Note: This installation helper must be run with root privileges.'
	@echo -e 'Note: This installation helper only copies the header files to "$(INC_PATH)".'
	@echo -e 'To compile your project, you need to link "$(LIB_TARGET)" just the same as you do with your objects files.'
	mkdir -p $(INC_PATH)
	cp -v $(LIB_HEADERS) $(INC_PATH)

uninstall:
	rm -rf $(INC_PATH)

examples: helloworld.o | $(LIB_TARGET)
	$(CC) -Wall -Wextra -o $(BUILD_DIR)/helloworld $(BUILD_DIR)/$< -Lbuild -ltermui

helloworld.o: $(BUILD_DIR)
	@echo -e "$(RED)Compiling$(RESET) $(YELLOW) ./tests/helloworld.c $(RESET) ---> $(GREEN) $@ $(RESET)"
	@$(CC) -c ./tests/helloworld.c -o $(BUILD_DIR)/$@

$(BUILD_DIR):
	mkdir -p $@

$(LIB_TARGET): $(LIB_OBJECTS) | $(BUILD_DIR)
	$(AR) rcs $@ $^

$(BUILD_DIR)/%.o: ./source/%.c $(LIB_HEADERS) | $(BUILD_DIR) info
	@echo -e "$(RED)Compiling$(RESET) $(YELLOW) $< $(RESET) ---> $(GREEN) $@ $(RESET)"
	@$(CC) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all install clean
