BUILD_DIR := build
CBUILD_DIR := $(BUILD_DIR)/c
CCBUILD_DIR := $(BUILD_DIR)/cc
SRC_DIR := src
MAIN_DIR := main
BIN_DIR := bin
LIB_DIR := lib
LIBS := linear_algebra sort
LIBS := $(LIBS:%=$(LIB_DIR)/lib%.a)

# source files
CMAINS := $(shell find $(MAIN_DIR) -name '*.c')
CCMAINS := $(shell find $(MAIN_DIR) -name '*.cc')
CSRCS := $(shell find $(SRC_DIR) -name '*.c')
CCSRCS := $(shell find $(SRC_DIR) -name '*.cc')

# binary files
COBJS := $(CMAINS:%.c=$(CBUILD_DIR)/%.o)
CCOBJS := $(CCMAINS:%.cc=$(CCBUILD_DIR)/%.o)
OBJS := $(COBJS) $(CCOBJS)
# only make executable for main files
MAINS := $(OBJS:%.o=%)
# add other binary files
CCOBJS += $(CCSRCS:%.cc=$(CCBUILD_DIR)/%.o)
COBJS += $(CSRCS:%.c=$(CBUILD_DIR)/%.o)
OBJS := $(COBJS) $(CCOBJS)

CPPFLAGS := $(INC_FLAGS) -Wall -g -Iinclude

ALL := $(LIBS) $(MAINS)
all: $(ALL)
	mkdir -p $(BIN_DIR)
	cp $(MAINS) $(BIN_DIR)

# C executable
$(CBUILD_DIR)/%: $(CBUILD_DIR)/%.o
	$(CC) $^ -o $@ $(LDFLAGS)

# C++ executable
$(CCBUILD_DIR)/%: $(CCBUILD_DIR)/%.o
	$(CXX) $^ -o $@ $(LDFLAGS)

# C object files
$(CBUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# C++ object files
$(CCBUILD_DIR)/%.o: %.cc
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

# library rules

COBJS_DIR := $(CBUILD_DIR)/$(SRC_DIR)
CCOBJS_DIR := $(CCBUILD_DIR)/$(SRC_DIR)

$(LIB_DIR)/liblinear_algebra.a: $(CCOBJS_DIR)/linear_algebra.o
	ar rcs $@ $^

$(LIB_DIR)/libsort.a: $(CCOBJS_DIR)/sort.o
	ar rcs $@ $^

# library rules end

# executable that uses library

$(CCBUILD_DIR)/$(MAIN_DIR)/linear_main: $(CCBUILD_DIR)/$(MAIN_DIR)/linear_main.o \
$(LIB_DIR)/liblinear_algebra.a
	$(CXX) $^ -o $@ $(LDFLAGS)

# executable that uses library end

.PHONY: clean
clean:
	-rm -r $(BUILD_DIR) $(BIN_DIR) $(LIB_DIR)/*