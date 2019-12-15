# Lem-in_42

Lem-In is the one but last project on 42's algorithm Branch.
It is summarized as follows: "This project is meant to make you code an ant farm manager.".

It's the first project that is mandatorily done in pairs, thus it's architecture is separated in two: the parser and the algorithm itself.
It's goal is to make a given number of ants go from the first to the last room through a set of subsidiary rooms and paths, in the smallest possible number of turns. A turn is when every ant moves forward by one room.
Knowing that: All rooms except start and end, have a finite capacity of one ant by turn. Links, end and start have infinite capacity.
Output is formatted as follows: Each line is one anthill update, each movement must start with character 'L'. Each ant is represented by its number of entrance in the anthill followed by the destination room.

```output_f("L%d-%s\n", ant_number, destination_room_name);```

As for the parser, I have used a hash table to optimize the complexity of the parsing when given large ant farms with numerous rooms and connections.
Indeed, the formatting of the input file is very specific. It requires:
1. A given number of ants, of at least one individual.
2. A set of rooms of different names with positive integers as coordinates. Coordinates are only useful if one decides to make a graphical representation of the ouput of the program.
3. A start room and an end one which are designated by the two modifiers (##start and ##end) on the rooms preceding line.
4. A set of links between rooms symbolised by the dash symbol ('-') that must create a path between the start and end rooms. (room1-room2)
5. The input can also take comments. Any line that starts with character "#" that isn'4t a required modifier (##end or ##start) will be considered a comment.

As for the algorithm, my collegue and I have implemented a version of the Edmund-Karp algorithm of Graph Theory.
To do that, once the input file read and validated, we allocate a linked-list (of typedef t_list structure) of all the known rooms. Each node then sees itself become the head of another list (of typedef t_paths) but this time of the known connections that given rooms has, in order of apparition during the parsing of links.

We therefore have a main list of t_list structures, each node having a pointer to a t_paths linked-list in which pointers to their t_list counterparts are found. Roughly a 2 dimensional linked-list.

Once the data structure is initialised, an Adjacency Matrix is set of size room_number^2. This is used during the algorithm Breadth-First Search, when each node is being probed to find possible paths.
Once a path is found, we calculate, given the number of ants, how many turns it would take to make them all go from ##start to ##end. We then store that value and retry path-finding while the paths we find take less turns than the ones we have already found.

This project is one of the more complex ones on the Algorithm Branch as it requires deep data-structure knowledge, and mathematical concepts implementation as well as a solid parser to prevent the numerous possible invalid inputs.
