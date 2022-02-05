all: criarTabuleiro.o jogabilidade.o controlarOjogo.o
	gcc criarTabuleiro.o jogabilidade.o controlarOjogo.o main.c -o p

criarTabuleiro.o: matriz.h
	gcc -c criarTabuleiro.c

jogabilidade.o: jogabilidade.h
	gcc -c jogabilidade.c

controlarOjogo.o: controlarOJogo.h
	gcc -c controlarOjogo.c

clean:
	rm -rf *.o

run:
	./p
