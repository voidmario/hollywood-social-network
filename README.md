Mario Reyes
01/10/2020

------------
DESCRIPTION

An edge list implementation of an undirected graph is built using IMDb movie data. An executable called
socialnetwork is made on running "make" in the terminal. The user provides an input file where each line corresponds to two actors in the form
"[ACTOR 1 FIRST NAME]\_[ACTOR 1 LAST NAME] [ACTOR 2 FIRST NAME]\_[ACTOR 2 LAST NAME]" whose path/link will be found, if it exists. The shortest 
path between these two actors is found through a modified version of Breadth First Search. This path is then printed to the output file in the format
<ACTOR> -(MOVIE)- <NEXT ACTOR>....

-----------
FILES

- socialnetwork.cpp

This file is the wrapper for the entire program. The main function is found here and all of the file traversing
as well as Graph creation and BFS printing takes place here.

- graph.cpp

This file contains all of the functions required by the Graph class such as addEdge, insertActors, and BFS.

- graph.h

This file is the header file for the Graph class. It contains all of the function signatures needed to compile properly.

- Makefile

This file compiles and generates the socialnetwork executable

- actordata.txt

This file contains IMDb data where every line starts with a movie title and is followed by the cast of that movie.

- input.txt

This file contains a few tests and is an input for the program

- correct_output.txt

This file contains the correct paths that should be generated by the program when run with input.txt 


------------------
INSTRUCTIONS

This program is intended to be run through the terminal by typing "make" and generating the executable socialnetwork.
To actually run the program, it should be in the format "./socialnetwork <INPUT FILE> <OUTPUT FILE>" where the input file 
is a text file with pairs of actor names with underscores instead of spaces and the output file is empty. Once the program 
finishes successfully the output file will contain "Not present" if either one or both of the actors aren't present in
the data or if there exists no path connecting both actors. It will print the actor's name if it was repeated or it will 
print the path connecting both actors in the format <ACTOR> -(MOVIE)- <NEXT ACTOR>...

------------------
SOURCES

- https://en.m.wikibooks.org/wiki/Data_Structures/Graphs

- https://www.geeksforgeeks.org/unordered_map-in-cpp-stl/
