CC = gcc
CPPC = g++
CFLAGS = -lmousemoverlib -lX11 -lXtst -lXinerama

all:
	$(CC) main.c -o main $(CFLAGS)
	$(CPPC) main.cpp -o maincpp $(CFLAGS)

clean:
	rm -f main
	rm -f maincpp
