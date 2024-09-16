 
# Makefile
CC = g++
CFLAGS = -Wall -std=c++17
TARGET = hello

all: $(TARGET)

$(TARGET): hello.cpp
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(TARGET)
 
