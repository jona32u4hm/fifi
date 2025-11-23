SRC = $(wildcard src/*.c)
INC = -I ./include/
LIBS = -L ./lib/ -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

ll:
	@gcc -Wall $(SRC) $(INC) $(LIBS) -o main

clean:
	rm -f $(TARGET)

