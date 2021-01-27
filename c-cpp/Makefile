# 添加文件搜索路径，不用搜索头文件，因为 gcc 会搜索
VPATH = source tmp

################ 纯粹的任务或编译别名 ################
.PHONY : test linear clean 24

# 通过 CFLAGS 和 CXXFLAGS 简化规则书写，并省去对象的编译规则
# 用于 make 命令，只能用于目标文件的隐式规则
# 副作用：不能指定对象文件的生成位置
FLAGS := CXXFLAGS='-g -I header' CFLAGS='-g -I header'


# 线性代数（作为规则编写的模板）
# Linear algebra varibles
LINEAR_MAIN := source/linear_main.cc	# 主函数文件的相对路径，使用 := 可以防止 Makefile 递归使用变量名
LINEAR_CC := linear_algebra.cc			# 要用到的源文件名字
LINEAR_O := $(LINEAR_CC:cc=o)			# :cc=o 表示将原变量的 cc 替换成 o
ALL_O += $(LINEAR_O)					# 加入到所有的目标文件变量，用于测试
# 别名，放在前面是为了给 make 默认使用，因为下面的规则不能直接使用
linear :								# 通过 FLAGS 指定头文件搜索路径
	make linear_main.out $(FLAGS)
# 没有指定 linear_algebra.o 的生成规则，由 make 隐式规则生成
# 通过在 VPATH 中搜索 linear_lagebra.cc，再规则别名里为 make 指定 FLAG 即可正常生成
# 不能直接使用，因为隐式规则不会自动指定头文件搜索路径，需要使用添加了 FLAG 的规则别名
linear_main.out : linear_main.cc $(LINEAR_O)
	g++ -g -I header -o linear_main.out $(LINEAR_MAIN) $(LINEAR_O)

# 测试规则
TEST_MAIN := source/test.cc
test :
	make test.out $(FLAGS)
test.out : test.cc $(ALL_O)				# 由于 ALL_O 用到了其他变量，所以要放到其他变量的后面
	g++ -g -I header -o test.out $(TEST_MAIN) $(ALL_O)

# TODO: refactor code below
# My varibles
MY_MAIN := source/my_main.cc
MY_CC := helper.cc sort.cc
MY_O := $(MY_CC:cc=o)
# ALL_O += $(MY_O)

# Stats variables	用于处理数据的代码文件
STATS_C := statistic.c
STATS_O := $(STATS_C:c=o) helper.o
# ALL_O += $(STATS_O)


################ 规则 ################

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

# GUN rules
all.tmp : $(ALL_O)
	-find * -type f -name '*.o' -exec echo {} > all.tmp \;

# 只用来删除 make 生成的文件
clean :
	-rm -f tmp/*.o *.out *.tmp *.o
	-find * -name '*\.out' -delete
	-find * -name '*\.exe' -delete

24 :
	make 24.out

my :
	make my.out $(FLAGS)

all :
	make all.tmp $(FLAGS)
