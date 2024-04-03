

project.exe : main.o cache.o divider_tree.o
	gcc main.o cache.o divider_tree.o -o project.exe -lm

main.o : main.c
	gcc -c -g main.c -o main.o -lm

cahce.o : cache.c
	gcc -c -g cache.c -o cache.o

divider_tree.o : divider_tree.c
	gcc -c -g divider_tree.c -o divider_tree.o

clean:
	rm -f *.o project.exe
