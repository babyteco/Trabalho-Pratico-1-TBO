CC = gcc
CFLAGS = -Wall -Wextra -g
LIBS = -lm
OBJ = main.o UnionFind.o ponto.o arvore.o aresta.o
EXEC = trab1

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LIBS)

main.o: main.c UnionFind.h ponto.h arvore.h aresta.h
	$(CC) $(CFLAGS) -c main.c

UnionFind.o: UnionFind.c UnionFind.h arvore.h ponto.h aresta.h
	$(CC) $(CFLAGS) -c UnionFind.c

ponto.o: ponto.c ponto.h
	$(CC) $(CFLAGS) -c ponto.c

arvore.o: arvore.c arvore.h ponto.h
	$(CC) $(CFLAGS) -c arvore.c

aresta.o: aresta.c aresta.h UnionFind.h
	$(CC) $(CFLAGS) -c aresta.c

clean:
	rm -f *.o $(EXEC)

run: all
	./$(EXEC) $(INPUT) $(K) $(OUTPUT)