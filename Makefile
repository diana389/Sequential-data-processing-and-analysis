# Declaratiile de variabile
CC = gcc
CFLAGS = -g -Wall -lm
 
# Regula de compilare
all: build

build: tema1.c
	$(CC) -o tema1 tema1.c $(CFLAGS)

# Regulile de "curatenie" (se folosesc pentru stergerea fisierelor intermediare si/sau rezultate)

clean:
	rm -f tema1
	rm -f *.o

