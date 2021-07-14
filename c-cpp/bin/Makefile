.PHONY : clean

quick.out : quick.cc
	g++ quick.cc -o quick.out -Wall

sum.out : quick.out
	ln -s `pwd`/quick.out sum.out

prefix.out : prefix.cc
	g++ prefix.cc -o prefix.out -Wall

diff.out : prefix.out
	ln -s `pwd`/prefix.out diff.out

complement.out : complement.cc
	g++ complement.cc -o complement.out -Wall

clean :
	rm *.out
