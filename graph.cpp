// Filename: graph.cpp
// 
// Implements all functions needed for the classes in
// the file "graph.h"
// 

#include "graph.h"
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#include <stack>

using namespace std;

// Graph constructor initializes vertices to zero
Graph :: Graph()
{
  vertices = 0;
}

// BFS(string source, string destination, ofstream &out): Finds and prints the shortest path between two provided actors to an output file
// Input: source which is the first actor, destination which is the second actor and out which is an output file to print to
// Output: None just prints out the shortest path between two actors to an output file
void Graph :: BFS(string source, string destination, ofstream &out)
{
    // Finds if both actors exist as vertices in the graph, if either one doesn't exist in the graph "Not present" will be printed
    if(adjList.find(source) == adjList.end() || adjList.find(destination) == adjList.end())
    {
      out << "Not present" << endl;
      return;
    }
    // Finds if both actors are really just the same actor but repeated,if it is, print that actor's name
    if(source == destination)
    {
      out << source << endl;
      return;
    }
    // Create a predecessor unordered map to keep track of the shortest path, create a queue to find the shortest path, and create
    // a stack to print the paths in the correct order (actor1 -> actor 2)
    unordered_map<string, string> predecessor;
    queue <string> q;
    stack<string> printOrder;

    q.push(source);

    while(!q.empty())
    {
        // Gets the front of the queue
        string current = q.front();
        q.pop();
        
        // Search through that actor's neighborhood to check if that neighbor has already been visited
        for(unordered_map<string, vector<string>> :: iterator it = adjList[current].begin(); it != adjList[current].end(); ++it)
        {
          string neighbor = (*it).first;
          // Finds if the neighbor has been visited or not, if it hasn't add it to the predecessor
          if(predecessor.find(neighbor) == predecessor.end())
          {
            predecessor[neighbor] = current;
            q.push(neighbor);
            
          }
        }  
    }
    // After BFS alg. finishes, if actor 2 is not present in the unordered map then print "Not present" 
    if(predecessor.find(destination) == predecessor.end())
    {
      out << "Not present" << endl;
      return;
    }
    // There exists a shortest path from actor 1 to actor 2
    else
    {
      // Push the path into a stack in order to print it out in the correct order
      string current = destination;
      printOrder.push(current);
      while(current != source)
      {
        current = predecessor[current];
        printOrder.push(current);   
      } 
      // The printing of the path between source and destination takes place here:
      // Pop the values from the stack to print them in the correct order
      string actor1 = printOrder.top();
      printOrder.pop();
      string actor2 = printOrder.top();
      printOrder.pop();
      string movie = adjList[actor1][actor2][0];
      
      out << actor1 << " -(" << movie << ")- " << actor2;
      while(!printOrder.empty())
      {
        actor1 = actor2;
        actor2 = printOrder.top();
        printOrder.pop();
        movie = adjList[actor1][actor2][0];
        out << " -(" << movie << ")- " << actor2;
      }
      out << endl;
    }  
}


// addEdge(string a1, string a2): Creates a bidirectional relationship between two actors where the edge is the movie they come out in
// Input: string 'a1' and string 'a2' are actors that came out together in movie 'm'
// Output: None, just adds both actors into the unordered map and adds both as neighbors of eachother with their movie in common
void Graph :: addEdge(string a1, string a2, string m)
{
  string movie = m;
  string actor1 = a1;
  string actor2 = a2;
  
  // WE DO THIS TWICE FIRST FOR ACTOR 1 AND THEN ACTOR 2 BECAUSE THEIR RELATIONSHIP IS BI-DIRECTIONAL (UNDIRECTED GRAPH)!
  // Finds if actor 1 exists as a vertex, then checks if actor 2 exists in actor 1's neighborhood
  if(adjList.find(actor1) != adjList.end())
  {
    // This is the case where both actors already share a relationship, we only need to update their shared movies
    if(adjList[actor1].find(actor2) != adjList[actor1].end())
    {
      adjList[actor1][actor2].push_back(movie);
    }
    // This is the case where actor 2 is not already a neighbor of actor 1 so we need to add them into the neighborhood
    else
    {
      vector<string> movieList;
      movieList.push_back(movie);
      adjList[actor1].insert({actor2, movieList});
    }  
  }
  // This is the case where neither actor 1 or actor 2 exist, so we create a new entry in the unordered map for actor 1 and add actor 2
  // into actor 1's neighborhood along with their shared movie 
  else
  {
    unordered_map<string, vector<string>> neighborhood;
    vector<string> movieList;
    movieList.push_back(movie);
    neighborhood.insert({actor2, movieList});
     
    adjList.insert({actor1, neighborhood});
    vertices++;
  }
  
  // Finds if actor 2 exists as a vertex, then checks if actor 1 exists in actor 2's neighborhood
  if(adjList.find(actor2) != adjList.end())
  {
    // This is the case where both actors already share a relationship, we only need to update their shared movies
    if(adjList[actor2].find(actor1) != adjList[actor2].end())
    {
      adjList[actor2][actor1].push_back(movie);
    }
     // This is the case where actor 1 is not already a neighbor of actor 2 so we need to add them into the neighborhood
    else
    {
      vector<string> movieList;
      movieList.push_back(movie);
      adjList[actor2].insert({actor1, movieList});
    }
  }
  // This is the case where neither actor 1 or actor 2 exist, so we create a new entry in the unordered map for actor 1 and add actor 1
  // into actor 2's neighborhood along with their shared movie 
  else
  {
    unordered_map<string, vector<string>> neighborhood;
    vector<string> movieList;
    movieList.push_back(movie);
    neighborhood.insert({actor1, movieList});
    
    adjList.insert({actor2, neighborhood});
    vertices++;
  }
  
}

// insertActors(string m, vector<string> a): Grabs a list of actors who share a movie and create bidirectional edges between all of them 
// Input: A string of the movie name and a vector of the movie cast
// Output: None, just builds the actual graph for every line of the input file in sixdegrees.cpp
void Graph :: insertActors(string m, vector<string> a)
{
  string movie = m;
  vector<string> actorList = a;
  
  // There is only one actor present in the actors list, has an empty neighborhood
  if(actorList.size() == 1)
  {
    string actor = actorList[0];
    unordered_map<string, vector<string>> neighborhood;
    adjList.insert({actor, neighborhood});
    vertices++;
  }
  else
  {
    // Case where there are more than one actors in a movie
    for(int i = 0; (unsigned)i < actorList.size(); i++)
    {
      for(int j = i+1; (unsigned) j < actorList.size(); j++)
      {
        if(actorList[i] == actorList[actorList.size()-1])
        {
          return;
        }
        string actor1 = actorList[i];
        string actor2 = actorList[j];
        addEdge(actor1, actor2, movie);
      }
    }
  }  
}
