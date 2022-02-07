main: main.o criarTabuleiro.o jogabilidade.o jogadaPC.o controlarOjogo.o
	gcc main.o criarTabuleiro.o jogabilidade.o jogadaPC.o controlarOjogo.o -o main

main.o: main.c matriz.h jogabilidade.h jogadaPC.h controlarOJogo.h
	gcc -c main.c

controlarOjogo.o: controlarOJogo.h
	gcc -c controlarOjogo.c

criarTabuleiro.o: criarTabuleiro.c matriz.h
	gcc -c criarTabuleiro.c

jogabilidade.o: jogabilidade.h     
	gcc -c jogabilidade.c

jogadaPC.o: jogadaPC.h matriz.h jogabilidade.h
	gcc -c jogadaPC.c

clean:
	rm -rf *.o main

run:
	./p