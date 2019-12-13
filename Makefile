DIRECTIVE = -fopenmp -Werror

all:
	rm -f *.out
	gcc $(DIRECTIVE) ex5.c -o ex5.out
	gcc $(DIRECTIVE) ex5-1.c -o ex5-1.out
	gcc $(DIRECTIVE) ex5-2.c -o ex5-2.out
	gcc $(DIRECTIVE) ex5-3.c -o ex5-3.out
	gcc $(DIRECTIVE) ex6.c -o ex6.out
	gcc $(DIRECTIVE) ex7.c -o ex7.out
	gcc $(DIRECTIVE) ex8.c -o ex8.out
	gcc $(DIRECTIVE) ex9.c -o ex9.out
	gcc $(DIRECTIVE) ex10.c -o ex10.out
	
%: 
	rm -f $@.out
	clear
	gcc $(DIRECTIVE) ex$@.c -o ex$@.out
	./ex$@.out $x

clear:
	rm -f *.out
