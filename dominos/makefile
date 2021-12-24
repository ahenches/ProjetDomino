#changer le nom des deux lignes suivantes si nécessaire
SOURCES = main.c mainDominos.c libGraphique.c
OUTPUT = resultat
LIB = -lm -lSDL -lSDL_ttf -lSDL_mixer
OPT = -Wall -g
OBJ = $(SOURCES:.c=.o)


SDL_CFLAGS = $(shell sdl-config --cflags)
SDL_LDFLAGS = $(shell sdl-config --libs)


all: $(OUTPUT)

clean: 
	rm $(OUTPUT) *.o ./*.o

$(OUTPUT): ./libGraphique.o $(OBJ)
	@gcc $^  -o $(OUTPUT)  $(SDL_CFLAGS) $(SDL_LDFLAGS) $(LIB)


./libGraphique.o: ./libGraphique.c
	@gcc   -c ./libGraphique.c -o ./libGraphique.o 


%.o: %.c
	@gcc $(OPT) -c $<  -o $@


