CC = xlc
CFLAGS = -g -q64

TARGET = project5loader
OBJ = project5loader.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -g -q64 -o $(TARGET) $(OBJ)

project5loader.o: project5loader.c loader.h
	$(CC) $(CFLAGS) -c project5loader.c

clean:
	rm -f *.o *.dbg a.out $(TARGET)
