SRCDIR = ./src
OBJDIR = ./obj
TESTDIR = ./tests
TESTOBJDIR = ./testobj
CFLAGS = -Wall -std=c++11 -I$(SRCDIR)
CDEBUGFLAGS = $(CFLAGS) -g -O0
GTESTDIR = /usr/gtest-1.7.0
TESTDEBUGFLAGS = $(TESTFLAGS) $(CDEBUGFLAGS)
CC = clang++
LFLAGS = -lglut -lGLU
TESTFLAGS = -I$(GTESTDIR) -I$(GTESTDIR)/include $(CFLAGS) -I$(SRCDIR)

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJDIR)/%.dbg.o : $(SRCDIR)/%.cpp
	$(CC) $(CDEBUGFLAGS) -o $@ -c $<

$(OBJDIR)/%.o : $(TESTDIR)/%.cpp
	$(CC) $(TESTFLAGS) -o $@ -c $<

$(OBJDIR)/%.dbg.o : $(TESTDIR)/%.cpp
	$(CC) $(TESTDEBUGFLAGS) -o $@ -c $<


OBJ = \
	$(OBJDIR)/Chip8.o \
	$(OBJDIR)/Render.o

DEBUG_OBJ = \
	$(OBJDIR)/Chip8.dbg.o \
	$(OBJDIR)/Render.dbg.o

TEST_OBJ = \
	$(OBJDIR)/gtest-all.o \
	$(OBJDIR)/gtest_main.o \
	$(OBJDIR)/Chip8_unittest.o 

TEST_DEBUG_OBJ = \
	$(OBJDIR)/gtest-all.dbg.o \
	$(OBJDIR)/gtest_main.dbg.o \
	$(OBJDIR)/Chip8_unittest.dbg.o

all: chip8 debug test test_debug

chip8: $(OBJDIR)/chip8_main.o $(OBJ)
	$(CC) $(OBJ) $(OBJDIR)/chip8_main.o $(LFLAGS) -o $@

debug: $(OBJDIR)/chip8_main.dbg.o $(DEBUG_OBJ)
	$(CC) $(DEBUG_OBJ) $(OBJDIR)/chip8_main.dbg.o $(LFLAGS) -o $@

test: $(OBJ) $(TEST_OBJ)
	$(CC) $(OBJ) $(TEST_OBJ) $(LFLAGS) -o $@ -lpthread $(GTESTDIR)/lib/.libs/libgtest.a

test_debug: $(DEBUG_OBJ) $(TEST_DEBUG_OBJ)
	$(CC) $(DEBUG_OBJ) $(TEST_DEBUG_OBJ) $(LFLAGS) -o $@ -lpthread $(GTESTDIR)/lib/.libs/libgtest.a

clean:
	\rm -f $(OBJDIR)/*.o
