# Used to build practice programs for CSAPP.

BUILD_DIR := build
SRC_DIR := src
BIN_DIR := bin
# contains library headers and sources
LIB_DIR := lib
LIBS := libmm.a libsbuf.a		# Except global libraries
GLOBAL_LIBS := libcsapp.so	# Global used libraries

SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJS := $(SRCS:%.c=$(BUILD_DIR)/%.o)
OUTS := $(SRCS:%.c=$(BUILD_DIR)/%)

CPPFLAGS := $(INC_FLAGS) -Wall -Werror -g -Ilib

all: $(OUTS)
	mkdir -p $(BIN_DIR)
	cp $^ $(BIN_DIR)

$(BUILD_DIR)/%: $(BUILD_DIR)/%.o $(GLOBAL_LIBS:%=$(BUILD_DIR)/%)
	$(CC) $^ -o $@ $(LDFLAGS)  

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Rules for libraries

# libcsapp.so
$(BUILD_DIR)/libcsapp.so: $(BUILD_DIR)/csapp.o
	$(CC) -shared -o $@ $^

$(BUILD_DIR)/csapp.o: $(LIB_DIR)/csapp.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) -fpic -c -o $@ $^

# libmm.a
$(BUILD_DIR)/libmm.a: $(LIB_DIR)/mm.o $(LIB_DIR)/memlib.o
	mkdir -p $(dir $@)
	ar rcs $@ $^

# libsbuf.a
$(BUILD_DIR)/libsbuf.a: $(LIB_DIR)/sbuf.o
	mkdir -p $(dir $@)
	ar rcs $@ $^

.PHONY: clean
clean:
	-rm -r $(BUILD_DIR) $(BIN_DIR)
	-rm $(LIB_DIR)/*.o
