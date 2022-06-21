CXX = g++
CFLAGS = -pthread -std=c++17 -Wall

SOURCES = parallel_dijkstra.cpp
OBJECTS = parallel_dijkstra.o

parallel_dijkstra: $(OBJECTS)
	$(CXX) $(CFLAGS) -o parallel_dijkstra $(OBJECTS)

parallel_dijkstra.o: parallel_dijkstra.cpp
	$(CXX) -c $(CFLAGS) -o parallel_dijkstra.o parallel_dijkstra.cpp

clean:
	rm -f *.o