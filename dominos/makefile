#changer le nom des deux lignes suivantes si nécessaire
SOURCES = main.c controleur.c vue.c modèle.c
OUTPUT = Dominos
LIB = -lm -lSDL -lSDL_ttf -lSDL_mixer 
OPT = -Wall -g
OBJ = $(SOURCES:.c=.o)


SDL_CFLAGS = $(shell sdl-config --cflags)
SDL_LDFLAGS = $(shell sdl-config --libs)


all: $(OUTPUT)

clean: 
	rm $(OUTPUT) *.o ./*.o

$(OUTPUT): ../lib/lib.o $(OBJ)
	@gcc $^  -o $(OUTPUT)  $(SDL_CFLAGS) $(SDL_LDFLAGS) $(LIB)
	rm *.o


../lib/lib.o: ../lib/lib.c
	@gcc   -c ../lib/lib.c -o ../lib/lib.o 


%.o: %.c
	@gcc $(OPT) -c $<  -o $@


