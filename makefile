OBJS = main.o MatrixStack.o XX.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

opgl : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o opgl

main.o : main.cpp MatrixStack.h XX.h
	$(CC) $(CFLAGS) main.cpp

MatrixStack.o : MatrixStack.cpp MatrixStack.h 
	$(CC) $(CFLAGS) MatrixStack.cpp

XX.o : XX.cpp XX.h MatrixStack.h
	$(CC) $(CFLAGS) XX.cpp

