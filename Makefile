CXX = g++
CXXFLAGS = -Wall

OBJECTS = graph.o socialnetwork.o

wordrange: $(OBJECTS)
	$(CXX) -g $(CXXFLAGS) -o socialnetwork graph.o socialnetwork.o

avl.o: graph.cpp graph.h
	$(CXX) -g $(CXXFLAGS) -c graph.cpp
	
wordrange.o: grap.cpp graph.h socialnetwork.cpp
	$(CXX) -g $(CXXFLAGS) -c socialnetwork.cpp

clean: 
	rm -f *.o
	rm socialnetwork
