BUILD_DIR := build
SRC_DIR := src
BIN_DIR := bin

SRCS := $(shell find $(SRC_DIR) -name '*.cc')
OBJS := $(SRCS:%.cc=$(BUILD_DIR)/%.o)
OUTS := $(SRCS:%.cc=$(BUILD_DIR)/%)

CPPFLAGS := $(INC_FLAGS) -Wall -g

all: $(OUTS)
	mkdir -p $(BIN_DIR)
	cp $^ $(BIN_DIR)

$(BUILD_DIR)/%: $(BUILD_DIR)/%.o
	$(CXX) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: %.cc
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	-rm -r $(BUILD_DIR) $(BIN_DIR)
