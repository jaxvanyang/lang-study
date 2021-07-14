.PHONY : clean
quick.out : quick.cc
	g++ quick.cc -o quick.out

sum.out : quick.out
	ln -s `pwd`/quick.out sum.out

prefix.out : prefix.cc
	g++ prefix.cc -o prefix.out

diff.out : prefix.out
	ln -s `pwd`/prefix.out diff.out

clean :
	rm *.out
