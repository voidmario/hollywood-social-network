// Filename: graphwrapper.cpp
// 
// Wrapper file for the undirected graph implementation used to calculate
// the shortest path between two actors, with a movie connecting adjacent actors
// 

#include "graph.h"
#include <iostream>
#include <stack>
#include <stdexcept>
#include <fstream>
#include <array>
#include <vector> 
#include <algorithm>
#include <sstream>
#include <cstring>

int main(int argc, char** argv)
{
    
    if (argc < 3) // must provide two arguments as input
    {
        throw std::invalid_argument("Usage: ./socialnetwork <INPUT FILE> <OUTPUT FILE>"); // throw error
    }
    
    ifstream movieInfo;
    ifstream input;
    ofstream output;

    input.open(argv[1]);
    movieInfo.open("cleaned_movielist.txt");
    output.open(argv[2]);
    
    string castInfo;
    string userInput;
    string word;
    vector<string> actors;

    Graph actorGraph;
  
    // Builds the graph we will be using to find the shortest path between two actors
    while(getline(movieInfo, castInfo))
    {
      istringstream iss(castInfo);
      actors.clear();
      iss >> word;
      string movie = word;
      
      while(iss >> word)
      {
        actors.push_back(word);
      }
      // This function builds the relationships between the cast of actors for this specific movie
      actorGraph.insertActors(movie, actors);     
    }
    movieInfo.close();
    
    // Prints out the shortest path between the actors provided in the input file 
    while(getline(input, userInput))
    {
      istringstream iss(userInput);
      
      string actor1;
      string actor2;
      iss >> actor1;
      iss >> actor2;
      
      // This function finds and prints the shortest path, if there is one, between two actors
      actorGraph.BFS(actor1, actor2, output);
    }
    output.close();
    input.close();
    
    
}