# 可以引入其他的 Makefile
# include ./linux-c/Makefile

# 添加文件搜索路径
VPATH = source

# Linear algebra varibles
LINEAR_MAIN := source/linear_main.cc	# 使用 := 可以防止 Makefile 递归使用变量名
LINEAR_CC := matrix.cc vector.cc
LINEAR_O := $(LINEAR_CC:cc=o)

# My varibles
MY_MAIN := source/my_main.cc
MY_CC := helper.cc sort.cc
MY_O := $(MY_CC:cc=o)

# Linear algebra rules
linear.out : linear_main.cc $(LINEAR_O)
	g++ -g -I header $(LINEAR_MAIN) $(LINEAR_O:%=tmp/%)

vector.o : vector.cc
	g++ -c -g -I header -o tmp/vector.o source/vector.cc

matrix.o : matrix.cc
	g++ -c -g -I header -o tmp/matrix.o source/vector.cc

# 24 points rules
24_points.out : 24_points.c
	cc -g source/24_points.c

# My rules
my.out : my_main.cc $(MY_O)
	g++ -g -I header $(MY_MAIN) $(MY_O:%=tmp/%)

helper.o : helper.cc
	g++ -c -g -I header -o tmp/helper.o source/helper.cc

sort.o : sort.cc
	g++ -c -g -I header -o tmp/sort.o source/sort.cc

.PHONY : linear clean 24
linear :
	make linear.out

clean :
	-rm -f tmp/*.o *.out

24 :
	make 24_points.out