# Used to build practice programs for CSAPP.

BUILD_DIR := build
SRC_DIR := src
BIN_DIR := bin
# contains library headers and sources
LIB_DIR := lib

SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJS := $(SRCS:%.c=$(BUILD_DIR)/%.o)
OUTS := $(SRCS:%.c=$(BUILD_DIR)/%)

CPPFLAGS := $(INC_FLAGS) -Wall -Werror -g -Ilib

all: $(OUTS)
	mkdir -p $(BIN_DIR)
	cp $^ $(BIN_DIR)

$(BUILD_DIR)/%: $(BUILD_DIR)/%.o $(BUILD_DIR)/libcsapp.so $(BUILD_DIR)/libmm.a
	$(CC) $^ -o $@ $(LDFLAGS) 

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# rule for libcsapp.so
$(BUILD_DIR)/libcsapp.so: $(BUILD_DIR)/csapp.o
	$(CC) -shared -o $@ $^

$(BUILD_DIR)/csapp.o: $(LIB_DIR)/csapp.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) -fpic -c -o $@ $^

# rule for libmm.a
$(BUILD_DIR)/libmm.a: $(BUILD_DIR)/mm.o $(BUILD_DIR)/memlib.o
	ar rcs $@ $^

$(BUILD_DIR)/mm.o: $(LIB_DIR)/mm.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) -fpic -c -o $@ $^

$(BUILD_DIR)/memlib.o: $(LIB_DIR)/memlib.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) -fpic -c -o $@ $^

.PHONY: clean
clean:
	-rm -r $(BUILD_DIR) $(BIN_DIR)
