CFLAGS = -Wall -g

#BIN := $(patsubst %.c, %.out, $(wildcard *.c))
#BIN := $(patsubst %.c, %, $(wildcard *.c))
BIN := $(patsubst %.c,build/%, $(wildcard *.c))
OBJ := $(patsubst %.c,build/%.o, $(wildcard *.c))

all: $(OBJ)
	clang $(CFLAGS) $(OBJ) -o $(BIN)

# Build OBJ(*.o) files to build/*.o
# Using Automatic Variables
# https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html
build/%.o : %.c
	mkdir -p $(@D)
	clang $(CFLAGS) -c $< -o $@

run:
	./$(BIN)

clean:
	rm -rf build
#	rm -rf build $(BIN)
#	rm -rf $(BIN)
