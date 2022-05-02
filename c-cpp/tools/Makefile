BUILD_DIR := build
CBUILD_DIR := $(BUILD_DIR)/c
CCBUILD_DIR := $(BUILD_DIR)/cc
SRC_DIR := src
BIN_DIR := bin

CSRCS := $(shell find $(SRC_DIR) -name '*.c')
CCSRCS := $(shell find $(SRC_DIR) -name '*.cc')
COBJS := $(CSRCS:%.c=$(CBUILD_DIR)/%.o)
CCOBJS := $(CCSRCS:%.cc=$(CCBUILD_DIR)/%.o)
OBJS := $(COBJS) $(CCOBJS)
OUTS := $(OBJS:%.o=%)

CPPFLAGS := $(INC_FLAGS) -Wall -Werror -g -Iinclude

all: $(OUTS)
	mkdir -p $(BIN_DIR)
	cp $^ $(BIN_DIR)

$(CBUILD_DIR)/%: $(CBUILD_DIR)/%.o
	$(CC) $^ -o $@ $(LDFLAGS)

$(CCBUILD_DIR)/%: $(CCBUILD_DIR)/%.o
	$(CXX) $^ -o $@ $(LDFLAGS)

$(CBUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(CCBUILD_DIR)/%.o: %.cc
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	-rm -r $(BUILD_DIR) $(BIN_DIR)
