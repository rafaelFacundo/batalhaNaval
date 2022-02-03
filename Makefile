all: criarTabuleiro.o jogabilidade.o
	gcc criarTabuleiro.o jogabilidade.o main.c -o p

criarTabuleiro.o: matriz.h
	gcc -c criarTabuleiro.c

jogabilidade.o: jogabilidade.h
	gcc -c jogabilidade.c

clean:
	rm -rf *.o

run:
	./p
