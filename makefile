CC=g++ -std=c++11 -Wall -Wpedantic -Werror
SOURCES=main.cpp in.cpp grid.cpp
EXECUTABLE=rectilinear_shortest_steiner_tree

all: $(EXECUTABLE)

$(EXECUTABLE):  $(SOURCES) *.hpp
	$(CC) -o $@ $(SOURCES)

clean:
	rm -f $(EXECUTABLE)