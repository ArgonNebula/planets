TARGET= v3
CC= g++
CFLAGS= -std=c++0x -O3 -Wall -Wextra
DEPS = planet.hpp starmap.hpp route.hpp
OBJ = v3.o planet.o starmap.o route.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o
	rm -f $(TARGET)

.PHONY: default all clean

