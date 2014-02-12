CC = g++
CFLAGS = -Wall -std=c++0x
SRCDIR = ./src
OBJDIR = ./obj

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

OBJ = \
	$(OBJDIR)/Chip8.o


all: chip8

chip8: $(OBJ)
	$(CC) $(OBJ) -o $@
