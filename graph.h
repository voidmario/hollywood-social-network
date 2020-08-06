// Filename: graph.h
// 
// Header file for the graph implementation, contains all classes used
// 

#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <cstdlib>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// The Graph class holds an unordered_map where the key is the name of an actor and the value is another unordered_map
// which is the actor's neighborhood. The key is a neighbor and the value is a vector of movies the actors share
class Graph
{
    private:
      int vertices;
      //    (vertex)    (neighborhood)  (movies together)
      // actor vertex -> actor2 vertex -> movie list
      unordered_map<string, unordered_map<string, vector<string>>> adjList;
      
    
    public:
      Graph();
      void addEdge(string, string, string);
      void insertActors(string, vector<string>);
      void BFS(string, string, ofstream&);
};

#endif