.PHONY : clean

random.out : random.cc
	g++ random.cc -o random.out -Wall

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

round.out : round.cc
	g++ round.cc -o round.out -Wall

discrete.out : discrete.cc
	g++ discrete.cc -o discrete.out -Wall

sort.out : sort.cc
	g++ sort.cc -o sort.out -Wall

clean :
	rm *.out
