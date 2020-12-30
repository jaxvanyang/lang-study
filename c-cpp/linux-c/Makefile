
# Target in out/
MAIN = main
STATS = stats
TEST = test

# Path of main/*.c
MAIN_C = MAIN/main.c
STATS_C = MAIN/stats.c
TEST_C = MAIN/test.c

# Path of main/*.h
MAIN_H = MAIN/main.h
STATS_H = MAIN/stats.h

# Path of source/*.c
HELPER_C = source/helper.c
SORT_C = source/sort.c
STATISTIC_C = source/statistic.c

# Path of header/*.h
HELPER_H = header/helper.h
SORT_H = header/sort.h
STATISTIC_H = header/statistic.h

# Path of object/*.c
HELPER_O = object/helper.o
SORT_O = object/sort.o
STATISTIC_O = object/statistic.o

# List of varibles
SOURCES = helper.c sort.c statistic.c
OBJS = helper.o sort.o statistic.o

# Path of list
SOURCES_PATH = $(patsubst %, source/%, $(SOURCES))
OBJS_PATH = $(patsubst %, object/%, $(OBJS))

# Prerequiste
MAIN_PREQ = $(OBJS_PATH) $(MAIN_H) $(MAIN_C)
STATS_PREQ = $(OBJS_PATH) $(STATS_H) $(STATS_C)
TEST_PREQ = $(OBJS_PATH) $(TEST_H) $(TEST_C)
# HELPER_PREQ = $(HELPER_H) $(HELPER_C)
# SORT_PREQ = $(SORT_H) $(SORT_C)
# STATISTIC_PREQ = $(STATISTIC_H) $(STATISTIC_C)

# Build rules
$(MAIN) : $(MAIN_PREQ)
	cc -g -o $(MAIN) -I header $(MAIN_PREQ)
	mv $(MAIN) out/

$(STATS): $(STATS_PREQ)
	cc -g -o $(STATS) -I header $(STATS_PREQ)
	mv $(STATS) out/

$(TEST) : $(TEST_PREQ)
	cc -g -o $(TEST) -I header $(TEST_PREQ)
	mv $(TEST) out/

$(HELPER_O) : $(HELPER_C)
	cc -c -g -I header $(HELPER_C)
	mv helper.o object/

$(SORT_O) : $(SORT_C)
	cc -c -g -I header $(SORT_C)
	mv sort.o object

$(STATISTIC_O) : $(STATISTIC_C)
	cc -c -g -I header $(STATISTIC_C)
	mv statistic.o object

run : out/main
	out/main

.PHONY : clean helper sort statistic

clean :
	-rm $(OBJS_PATH)
	-rm out/*

helper : 
	make $(HELPER_O)

sort :
	make $(SORT_O)

statistic :
	make $(STATISTIC_O)