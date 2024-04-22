TARGET=main
CC=g++
DEBUG=-g
OPT=-O0
WARN=-Wall
CURSES=-lncurses
TINFO=-ltinfo
CCFLAGS=$(DEBUG) $(OPT) $(WARN)
LD=g++
OBJS=main.cpp piece.cpp test.cpp textrenderer.cpp board.cpp gameengine.cpp

all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(DEBUG) $(OPT) $(WARN) $(CURSES) $(TINFO)

main.cpp: main.cpp
	$(CC) -c $(CCFLAGS) main.cpp

piece.cpp: piece.cpp
	$(CC) -c $(CCFLAGS) piece.cpp

test.cpp: test.cpp
	$(CC) -c $(CCFLAGS) test.cpp

textrenderer.cpp: textrenderer.cpp
	$(CC) -c $(CCFLAGS) textrenderer.cpp

board.cpp: board.cpp
	$(CC) -c $(CCFLAGS) board.cpp

gameengine.cpp : gameengine.cpp
	$(CC) -c $(CCFLAGS) gameengine.cpp

clean:
	rm -f *.o $(TARGET)
