SRCDIR = ./src
OBJDIR = ./obj
TESTDIR = ./tests
TESTOBJDIR = ./testobj
CFLAGS = -Wall -std=c++11 -I$(SRCDIR)
CDEBUGFLAGS = $(CFLAGS) -g -O0
GTESTDIR = /usr/gtest-1.7.0
TESTDEBUGFLAGS = $(TESTFLAGS) 
CC = clang++
LFLAGS = -lglut -lGLU -lGL
TESTFLAGS = -I$(GTESTDIR) -I$(GTESTDIR)/include 

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJDIR)/%.dbg.o : $(SRCDIR)/%.cpp
	$(CC) $(CDEBUGFLAGS) -o $@ -c $<

$(OBJDIR)/%.o : $(TESTDIR)/%.cpp
	$(CC) $(CFLAGS) $(TESTFLAGS) -o $@ -c $<

$(OBJDIR)/%.dbg.o : $(TESTDIR)/%.cpp
	$(CC) $(CDEBUGFLAGS) $(TESTDEBUGFLAGS) -o $@ -c $<


OBJ = \
	$(OBJDIR)/Chip8.o \
	$(OBJDIR)/Render.o \
	$(OBJDIR)/KeyPad.o

DEBUG_OBJ = \
	$(OBJDIR)/Chip8.dbg.o \
	$(OBJDIR)/Render.dbg.o \
	$(OBJDIR)/KeyPad.dbg.o

GTEST_OBJ = \
	$(OBJDIR)/gtest-all.o \
	$(OBJDIR)/gtest_main.o \

TEST_OBJ = \
	$(OBJDIR)/Chip8_unittest.o \
	$(OBJDIR)/Render_unittest.o \
	$(OBJDIR)/KeyPad_unittest.o 

TEST_DEBUG_OBJ = \
	$(OBJDIR)/Chip8_unittest.dbg.o \
	$(OBJDIR)/Render_unittest.dbg.o \
	$(OBJDIR)/KeyPad_unittest.dbg.o

all: chip8 debug test test_debug

chip8: $(OBJDIR)/chip8_main.o $(OBJ)
	$(CC) $(OBJ) $(OBJDIR)/chip8_main.o $(LFLAGS) -o $@

debug: $(OBJDIR)/chip8_main.dbg.o $(DEBUG_OBJ)
	$(CC) $(DEBUG_OBJ) $(OBJDIR)/chip8_main.dbg.o $(LFLAGS) -o $@

test: $(OBJ) $(GTEST_OBJ) $(TEST_OBJ)
	$(CC) $(OBJ) $(GTEST_OBJ) $(TEST_OBJ) $(LFLAGS) -o $@ -lpthread $(GTESTDIR)/lib/.libs/libgtest.a

test_debug: $(DEBUG_OBJ) $(GTEST_OBJ) $(TEST_DEBUG_OBJ)
	$(CC) $(DEBUG_OBJ) $(GTEST_OBJ) $(TEST_DEBUG_OBJ) $(LFLAGS) -o $@ -lpthread $(GTESTDIR)/lib/.libs/libgtest.a

clean:
	\rm -f $(OBJDIR)/Chip8_main.dbg.o $(OBJDIR)/Chip8_main.o $(OBJ) $(DEBUG_OBJ) $(TEST_OBJ) $(TEST_DEBUG_OBJ)
