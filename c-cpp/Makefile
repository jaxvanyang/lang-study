# 可以引入其他的 Makefile
# include ./linux-c/Makefile

# 添加文件搜索路径，不用搜索头文件，因为 gcc 会搜索
VPATH = source tmp


################ 变量 ################
# Linear algebra varibles
LINEAR_MAIN := source/linear_main.cc	# 使用 := 可以防止 Makefile 递归使用变量名
LINEAR_CC := matrix.cc vector.cc
LINEAR_O := $(LINEAR_CC:cc=o)
ALL_O += $(LINEAR_O)	# 添加所有的对象文件名，方便测试

# My varibles
MY_MAIN := source/my_main.cc
MY_CC := helper.cc sort.cc
MY_O := $(MY_CC:cc=o)
ALL_O += $(MY_O)

# Stats variables	用于处理数据的代码文件
STATS_C := statistic.c
STATS_O := $(STATS_C:c=o) helper.o
ALL_O += $(STATS_O)


################ 规则 ################
# Linear algebra rules
linear.out : linear_main.cc $(LINEAR_O)
	g++ -g -I header -o linear.out $(LINEAR_MAIN) $(LINEAR_O)

# 24 points rules
24.out : 24_points.c
	cc -g -o 24.out source/24_points.c

# My rules
my.out : my_main.cc $(MY_O)
	g++ -g -I header -o my.out $(MY_MAIN) $(MY_O)

# stats rules
stats.out : stats.c $(STATS_O)
	g++ -g -I header -o stats.out source/stats.c $(STATS_O)

statistic.o : statistic.c
	g++ -c -g -I header source/statistic.c

# Test rules
test.out : test.cc $(ALL_O)
	g++ -g -I header -o test.out source/test.cc $(ALL_O:%=tmp/%)

# GUN rules
all.tmp : $(ALL_O)
	-find * -type f -name '*.o' -exec echo {} > all.tmp \;


################ 纯粹的任务或编译别名 ################
.PHONY : linear clean 24

# 只用来删除 make 生成的文件
clean :
	-rm -f tmp/*.o *.out *.tmp *.o
	-find * -name '*\.out' -delete


################ 规则别名 ################
# 通过 CFLAGS 和 CXXFLAGS 简化规则书写，并省去对象的编译规则
# 只能用于对象文件的编译
# 副作用：不能指定对象文件的生成位置
FLAGS := CXXFLAGS='-g -I header' CFLAGS='-g -I header'
linear :
	make linear.out $(FLAGS)

24 :
	make 24.out

my :
	make my.out $(FLAGS)

test :
	echo $(STATS_O)
	echo $(ALL_O)

all :
	make all.tmp $(FLAGS)