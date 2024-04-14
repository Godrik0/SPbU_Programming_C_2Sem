

project.exe : main.o cache.o divider_tree.o
	gcc main.o -ggdb3 cache.o divider_tree.o -o project.exe -lm

main.o : main.c
	gcc -c -g -ggdb3 main.c -o main.o -lm

cahce.o : cache.c
	gcc -c -ggdb3  -g cache.c -o cache.o

divider_tree.o : divider_tree.c
	gcc -c -g -ggdb3 divider_tree.c -o divider_tree.o

clean:
	rm -f *.o project.exe
