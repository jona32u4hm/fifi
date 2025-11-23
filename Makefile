SRC     = $(wildcard src/*.c)
OBJDIR  = build
OBJ     = $(patsubst src/%.c,$(OBJDIR)/%.o,$(SRC))
INC     = -Iinclude
LIBS    = -Llib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
TARGET  = main

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) $(INC) $(LIBS) -o $(TARGET)

# Regla para generar objetos en build/
$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(OBJDIR)
	$(CC) -Wall -c $< -o $@ $(INC)

clean:
	rm -rf $(OBJDIR) $(TARGET)

