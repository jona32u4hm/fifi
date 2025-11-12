
TARGET = finding_fifi

SRC_FILES = $(wildcard src/*.c)

# $^ list of dependencies
# $@ target name

all: $(TARGET)

$(TARGET): $(SRC_FILES)
	gcc -Wall $^ -I ./include/ -L ./lib/ -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o $@ 





clean:
	rm -f $(TARGET)
