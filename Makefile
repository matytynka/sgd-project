IDIR = include
LDIR = lib
ODIR = build
SDIR = src

CC=g++
CFLAGS=-I$(IDIR) -L$(LDIR) -w -lmingw32 -lSDL2main -lSDL2 -std=c++11 -o $@

_DEPS = 
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = test.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c $< $(CFLAGS)

build/game: $(OBJ)
	$(CC) $^ $(CFLAGS)