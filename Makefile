DIRECTIVE = -fopenmp -Werror

all:
	gcc $(DIRECTIVE) ex1.c -o ex1.out
	gcc $(DIRECTIVE) ex2.c -o ex2.out
	gcc $(DIRECTIVE) ex3.c -o ex3.out
	gcc $(DIRECTIVE) ex4.c -o ex4.out
	gcc $(DIRECTIVE) ex5.c -o ex5.out
	gcc $(DIRECTIVE) ex5-1.c -o ex5-1.out
	gcc $(DIRECTIVE) ex5-2.c -o ex5-2.out
	gcc $(DIRECTIVE) ex5-3.c -o ex5-3.out

	gcc $(DIRECTIVE) ex7.c -o ex7.out
	gcc $(DIRECTIVE) ex8.c -o ex8.out

%:
	clear
	gcc $(DIRECTIVE) ex$@.c -o ex$@.out
	./ex$@.out $x
