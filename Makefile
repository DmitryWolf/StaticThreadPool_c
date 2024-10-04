CC = gcc
CFLAGS = -fdiagnostics-color=always -g -fsanitize=thread -O0 -Iinclude
SRC = src/*.c
TARGET = main

all: run

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
