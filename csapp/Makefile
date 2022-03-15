BUILD_DIR := ./build
SRC_DIRS := ./

SRCS := $(shell find $(SRC_DIRS) -name '*.c')
OBJS := $(SRCS:%.c=$(BUILD_DIR)/%.o)
OUTS := $(SRCS:%.c=$(BUILD_DIR)/%)

CPPFLAGS := $(INC_FLAGS) -Wall -g

all: $(OUTS)

# run $(BUILD_DIR)/target
%: $(BUILD_DIR)/%
	$^

$(BUILD_DIR)/%: $(BUILD_DIR)/%.o
	$(CC) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -r $(BUILD_DIR)