CFLAGS = -O3 `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs`
INC = sdl2-light.h graphismes.h world.h eventsMain.h constante.h
SRC = main.c sdl2-light.c graphismes.c world.c eventsMain.c
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

