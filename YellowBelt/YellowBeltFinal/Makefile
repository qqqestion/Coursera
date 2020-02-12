CC = clang++
CFLAGS = -std=c++17 -I$(IDIR)

IDIR = ./include/
SRCDIR = ./src/*

SOURCES = $(SRCDIR)*.cpp

all: clean app run clean

app:
	$(CC) $(SRCDIR) $(CFLAGS) -o $@

run:
	./app 2>error.txt
	
clean:
	rm -f app
