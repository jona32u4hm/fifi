

all:
	@gcc -Wall src/player.c -I ./include/ -L ./lib/ -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o main
