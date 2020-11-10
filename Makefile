all: principal.o
	gcc -o all principal.o

principal.o:
	gcc -c principal.c

clean:
	rm all principal.o