
CC	= gcc
CXX	= g++ -std=c++11
CFLAGS = -Wall -g -lpcap

PROGS = main
OBJ = src/array.o main.o

all: $(PROGS)

%.o: %.c
	$(CC) $< $(CFLAGS) -c -o $@

%.o: %.cpp
	$(CXX) $< $(CFLAGS) -c -o $@

$(PROGS): $(OBJ)
	$(CC) $^ $(CFLAGS) -o $@

clean:
	rm -f *~ $(PROGS) $(OBJ)

run:
	./$(PROGS)
