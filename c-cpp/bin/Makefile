.PHONY : clean

prime.out : prime.cc
	g++ prime.cc -o prime.out -Wall

min_repr.out : min_repr.cc
	g++ min_repr.cc -o min_repr.out -Wall

match.out : match.cc
	g++ match.cc -o match.out -Wall

calc.out : calc.cc
	g++ calc.cc -o calc.out -Wall

log2.out : log2.cc
	g++ log2.cc -o log2.out -Wall

random.out : random.cc
	g++ random.cc -o random.out -Wall

power.out : power.cc
	g++ power.cc -o power.out -Wall

sum.out : power.out
	ln -s `pwd`/power.out sum.out

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
