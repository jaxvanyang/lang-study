.PHONY : clean

quick_sort.out : quick_sort.cc
	g++ quick_sort.cc -o quick_sort.out

random.out : random.cc
	g++ random.cc -o random.out

quick_sort_test : quick_sort.out random.out
	./random.out && ./quick_sort.out < data.in > data.out

test.out : test.cc
	g++ test.cc -o test.out

clean :
	rm *.out *.exe

remove :
	rm data.in data.out