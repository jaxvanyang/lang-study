# directories
CSRC_DIR := csrc
CCSRC_DIR := ccsrc
BUILD_DIR := build
CBUILD_DIR := $(BUILD_DIR)/$(CSRC_DIR)
CCBUILD_DIR := $(BUILD_DIR)/$(CCSRC_DIR)
BIN_DIR := bin
CLIB_DIR := clib
CCLIB_DIR := cclib
CLIB_BUILD := $(BUILD_DIR)/$(CLIB_DIR)
CCLIB_BUILD := $(BUILD_DIR)/$(CCLIB_DIR)

# source files
CSRCS := $(shell find $(CSRC_DIR) -name '*.c')
CCSRCS := $(shell find $(CCSRC_DIR) -name '*.cc')

# binary files
COBJS += $(CSRCS:%.c=$(BUILD_DIR)/%.o)
CCOBJS += $(CCSRCS:%.cc=$(BUILD_DIR)/%.o)
OBJS := $(COBJS) $(CCOBJS)
OUTS := $(OBJS:%.o=%)

CPPFLAGS := $(INC_FLAGS) -Wall -g -Iinclude

all: $(OUTS)
	mkdir -p $(BIN_DIR)
	cp $(OUTS) $(BIN_DIR)

# C executable
$(CBUILD_DIR)/%: $(CBUILD_DIR)/%.o
	$(CC) $^ -o $@ $(LDFLAGS)

# C++ executable
$(CCBUILD_DIR)/%: $(CCBUILD_DIR)/%.o
	$(CXX) $^ -o $@ $(LDFLAGS)

# C object files
$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# C++ object files
$(BUILD_DIR)/%.o: %.cc
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

# library rules begin

$(CCLIB_BUILD)/liblinear_algebra.a: $(CCLIB_DIR)/linear_algebra.o
	mkdir -p $(dir $@)
	ar rcs $@ $^

$(CCLIB_BUILD)/libsort.a: $(CCLIB_DIR)/sort.o
	mkdir -p $(dir $@)
	ar rcs $@ $^

# library rules end

# executable that uses library begin

$(CCBUILD_DIR)/linear_main: $(CCBUILD_DIR)/linear_main.o \
$(CCLIB_BUILD)/liblinear_algebra.a
	$(CXX) $^ -o $@ $(LDFLAGS)

# executable that uses library end

.PHONY: clean
clean:
	-rm -r $(BUILD_DIR) $(BIN_DIR) $(CLIB_DIR)/*.o $(CCLIB_DIR)/*.o
