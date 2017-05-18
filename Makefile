CFLAGS=-O3

ifdef DEBUG
	CFLAGS=-Wall -Werror -g
endif

BIOME_DIR=biome

all: life mutator

life:
	gcc $(CFLAGS) -o $(BIOME_DIR)/life life.c

mutator:
	gcc $(CFLAGS) -o mutator mutator.c

run:
	./$(BIOME_DIR)/life
	./mutator $(BIOME_DIR)

clean:
	rm -r $(BIOME_DIR)
	mkdir $(BIOME_DIR)
	rm mutator
