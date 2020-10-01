FLAGS = -W -Wall -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -fstack-protector-all -Wfloat-equal -Wpointer-arith -Wwrite-strings -Wcast-align -Wno-long-long -Wmissing-declarations -O3

all: a.out

mrproper:
	rm *.o *.out

a.out: main.o solve.o integrate.o  f.o f_integral.o interp.o heapsort.o
	gcc $(FLAGS) main.o solve.o integrate.o f.o f_integral.o interp.o heapsort.o -lm -o a.out
main.o: main.c
	gcc -c $(FLAGS) main.c -o main.o
solve.o: solve.c
	gcc -c $(FLAGS) solve.c -o solve.o
integrate.o:
	gcc -c $(FLAGS) integrate.c -o integrate.o
f.o: f.c
	gcc -c $(FLAGS) f.c -o f.o
f_integral.o:
	gcc -c $(FLAGS) f_integral.c -o f_integral.o
interp.o:
	gcc -c $(FLAGS) interp.c -o interp.o
heapsort.o:
	gcc -c $(FLAGS) heapsort.c -o heapsort.o
