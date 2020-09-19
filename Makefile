CXX = g++
CXXFLAGS = -Wall

OBJECTS = graph.o socialnetwork.o

socialnetwork: $(OBJECTS)
	$(CXX) -g $(CXXFLAGS) -o socialnetwork graph.o socialnetwork.o

graph.o: graph.cpp graph.h
	$(CXX) -g $(CXXFLAGS) -c graph.cpp
	
socialnetwork.o: graph.cpp graph.h socialnetwork.cpp
	$(CXX) -g $(CXXFLAGS) -c socialnetwork.cpp

clean: 
	rm -f *.o
	rm socialnetwork
