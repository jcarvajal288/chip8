CC = clang++
CFLAGS = -Wall -std=c++11
LFLAGS = -lglut
SRCDIR = ./src
OBJDIR = ./obj

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

OBJ = \
	$(OBJDIR)/Chip8.o \
	$(OBJDIR)/Screen.o


all: chip8

chip8: $(OBJ)
	$(CC) $(OBJ) $(LFLAGS) -o $@

clean:
	\rm -f $(OBJ)
