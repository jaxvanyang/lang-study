# 可以引入其他的 Makefile
# include ./linux-c/Makefile

# 添加文件搜索路径
VPATH = source

# 使用 := 可以防止 Makefile 递归使用变量名
LINEAR_MAIN := source/linear_main.cc
LINEAR_CC := matrix.cc vector.cc
LINEAR_O := $(LINEAR_CC:cc=o)


linear.out : linear_main.cc $(LINEAR_O)
	g++ -g -I header -o linear.out $(LINEAR_MAIN) $(LINEAR_O:%=tmp/%)

vector.o : vector.cc
	g++ -c -g -I header -o tmp/vector.o source/vector.cc

matrix.o : matrix.cc
	g++ -c -g -I header -o tmp/matrix.o source/vector.cc

test :
	echo "$(LINEAR_CC)"
	echo "$(LINEAR_O)"

.PHONY : linear clean
linear :
	make linear.out

clean :
	-rm -f tmp/*.o *.out