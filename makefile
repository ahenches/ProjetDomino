#changer le nom des deux lignes suivantes si nécessaire
SOURCE = main.c triominos/vue.c
OUTPUT = a.out
LIB = -lm -lSDL -lSDL_ttf
OPT = -Wall


SDL_CFLAGS = $(shell sdl-config --cflags)
SDL_LDFLAGS = $(shell sdl-config --libs)


all: $(OUTPUT)

clean: $(OUTPUT)
	rm $(OUTPUT) *.o

$(OUTPUT): lib/lib.o source.o
	@gcc lib/lib.o source.o -o $(OUTPUT)  $(SDL_CFLAGS) $(SDL_LDFLAGS) $(LIB)


lib/libgraphique.o: lib/lib.c
	@gcc   -c lib/lib.c -o lib/lib.o 

source.o: $(SOURCE)
	@gcc $(OPT) -c $(SOURCE)  -o source.o





