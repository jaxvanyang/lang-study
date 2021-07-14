.PHONY : clean
quick.out : quick.cc
	g++ quick.cc -o quick.out

sum.out : quick.out
	ln -s `pwd`/quick.out sum.out

clean :
	rm *.out
