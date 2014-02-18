CC=clang++
LD=clang++
CFLAGS=-W -Wall -Werror -Wextra -ansi -pedantic -O2
LDFLAGS=-lSDL
EXEC=fractal

SRC=src/main.cpp src/program.cpp src/canvas.cpp src/event.cpp src/color.cpp
SRC+=src/window.cpp src/fractal.cpp src/mandelbrot.cpp src/palette.cpp
SRC+=src/view.cpp src/zoompan.cpp src/vector2.cpp
OBJ=$(SRC:.cpp=.o)

all: $(OBJ)
	$(LD) $(LDFLAGS) $(OBJ) -o $(EXEC)

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean::
	rm -rf src/*.o
