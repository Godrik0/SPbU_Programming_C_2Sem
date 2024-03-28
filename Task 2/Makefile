

project.exe : main.o cache.o
	gcc main.o cache.o -o project.exe -lm

main.o : main.c
	gcc -c main.c -o main.o -lm

cahce.o : cache.c
	gcc -c cache.c -o cache.o

clean:
	rm -f *.o project.exe
