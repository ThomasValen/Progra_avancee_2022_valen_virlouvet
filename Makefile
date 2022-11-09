CFLAGS = -O3 `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs` -lSDL2_ttf -lm 

INC = sdl2-light.h graphismes.h world.h constante.h
SRC = main.c graphismes.c world.c sdl2-light.c
OBJ = $(SRC:%.c=%.o)

PROG = jeu

%.o: %.c $(INC)
	gcc $(CFLAGS) -c $<

jeu: $(OBJ)
	gcc $(CFLAGS) $(OBJ) $(LDFLAGS) -o $@

doc: $(PROG)
	doxygen ./$(PROG)
	make -C latex

clean:
	rm -f *~ *.o $(PROG)
	rm -rf latex html

