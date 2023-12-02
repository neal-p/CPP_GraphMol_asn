# Assignment #4 Graph Theory and Parallel Computations

## Problem 1. Molecular Structures using Graphs

### 1.1 Graph Theory

I chose to create a `GraphBase` class that would serve as the basis for a graph structure and implement many of the common graph tasks, then created child classes that implement the specific adjacency list and matrix list edge storage paradigms. 

For example, the `GraphBase` defines the following:
  - whether graph is directed or undirected 
  - number of edges
  - number of vertices
  - edge ids
  - edge pairs
  - printing
  - BFS (using the virtual getNeighbors function)
  - distance matrix (using BFS, which calls virtual getNeighbors function)
  - attribute handling**

This allowed me to be as DRY as possible, separating only the actually different aspects of adjacency list versus adjacency matrix in their respective child classes.

**
Futhermore, I wanted to challenge myself to mimic some of the graph analysis features that I am familiar with in RDKit and IGraph (both of which I use extensively for work). Both these libraries allow users to define node/attribute features of various types at runtime. I realized how suprisingly complex this feature was and wanted to attempt to build it into my graphs for this assignment. 
To facilitate different typed vertex and edge attributes, I created a base `Attribute` class and a templated `AttributeValue` class that inherits from `Attribute` and actually stores the values for the particular attribute type. Then, in my `GraphBase` I have a map of `v_attr_` which stores the name of the attribute mapped to a vector of pointers to `Attributes`. This allows me to create instances of `AttributeValue` with a particular type that are stored as pointers to an `Attribute`. Then, when retrieving or using the values, I can use `dynamic_cast` to cast the base `Attribute` back to the desired `AttributeValue<T>` type!

Because of these templated attribute features, the `GraphBase` is provided in the `include/graph_base.h` header file, allowing maximum flexibility in terms of user defined Vertex and Edge attribute types!
To provide differentiation between directed and undirected graphs, I define to-from as the row and from-to as the column. Therefore, in a undirected class the row and column at a particular index are equal, but this is not necessarily true for a directed graph unless all edges are explicitly created in both directions.


#### 1.1.1

Inheriting from the `GraphBase`, I define `Graph_AM` in `include/graph_am.h` as my implementation of the adjacency matrix representation of a graph. 

Here, I use a vector of vectors to maintain a square matrix where `0` represents no edge and `1` represents an edge between the two vertices. Then, I override the virutal function `getNeighbors` to iterate over the respective row of the adjacency matrix for the given vertex argument and build a neighbors vector with all the non-zero element indicies.

#### 1.1.2

Inheriting from the `GraphBase`, I define `Graph_AL` in `include/graph_al.h` as my implementation of the adjacency list representation of a graph. 

Here, I again use a vector of vectors, but now store just the neighbors for each vertex. To overridde the `getNeighbors` function, I simply return the vector of neighbors already stored in the adjacency list for the requested vertex id.

#### 1.1.3

I created an extensive testing protocol that tests all the aspects of the graph storage methods, adding vertices, adding edges, retrieving edge ids from a pair of vertices, getting neighbors, proper handling of directed/undirected, etc. 

The test can be found in `test/test_graph_al_directed.cpp`, `test/test_graph_al_undirected.cpp`, `test/test_graph_am_directed.cpp`, `test/test_graph_am_undirected.cpp`.

All tests can me compiled to executable files placed in the `bin` directory by invoking the makefiles `all` target. There are assert statements throughout the test programs that will test for proper conditions. If all tests pass, `ALL TESTS PASSED` will be printed and the program will return `0`. 

#### 1.1.4

THIS IS IMPORTANT DO LAST


### 1.2 Breadth First Search (BFS)

#### 1.2.1

I implemented `BFS` as a method of the `GraphBase` class (found in `/include/graph_base.h`), which interacts with the different edge storage paradigms using their respective `getNeighbors` functions. This allowed me to provide a common interface and again maintain DRY code. 

To color the different vertices, set the `pi` value showing their parent vertex in the search path, and the current distance, I set `_color` (enum of `Colors`) `_distance` (int),and `_pi` (int) vertex attributes with the dynamic typed attribute setting cababilities described above. The templated attributes allowed me to very easily create, set, and retrieve the necessary designations for the BFS. 

I wrote a few test cases to ensure the BFS was correctly working for directed and undirected graphs with both adjacency matrix and adjacency list representations. First, I create a graph with a few connected vertices and one non-connected vertex. I use `BFS` to check that the non-connected vertex can only reach itself. Then I check whether the connected vertices can reach all of each other, but not the non-connected vertex. Finally, I add a new edge from the non-connected vertex to the rest of the vertices and check that now all vertices are found by `BFS`.

#### 1.2.2

My choice to implement the `BFS` at the baseclass level makes it so that I did not have to choose which edge paradigm to implement it for! By providing a consistent API of `getNeighbors` for the adjacency list and adjacency matrix, I was able to provide better functionality in the baseclass. But, if I did need to choose, having the adjacency list provide direct access to neighbors without having to iterate over the row in the adjacency matrix and filter to `1`s would be my choice. This is because getting the neighbors in BFS is the most important manipulation of the underlying graph data.

For example, given vertex `V`, the BFS algorithm needs to retrieve all neighbors for `V`, then all neighbors for all of those neighbors. The adjacency list stores these neighbors in memory with O(1) lookup access. In contrast, we would need to iterate over all elements in the row of the adjacency matrix to find non-zero elements, which are the neighbors. Therefore, this is an O(n) operation for the adjacency matrix. For a small graph like the examples, the timing differences may not be noticable as `n` is small, but as `n` grows and the number of edges in the graph also grows, there will be many many more calls to `getNeighbors` to exhaustively search all vertices.

While adjacency list provides fast access to neighbors and is particularly memory efficient for sparse graphs since it only needs to store the edges that exist, disadvantages of the adjacency list approach is that it can be memory inefficient for large, dense graphs and poor for testing edge existance. This is especially true compared to an optimized undirected graph which could store the upper-triangle of the adjacency matrix to save space. Further, which the lookup of neighbors is O(1), to test for the existance of a particular edge is an O(n) operation. This is because you would need to iterate over the list of neighbors to determine if a particular node was contained in the adjaecncy list. There are some optimizations that could be applied, such as using a set instead of a normal list, but as implemented the test for if there is an edge between vertices 1 and 3 is an O(n) operation. 

Ultimately, the complexity of `BFS` comes from retrieving neighbors, not determining the presence of an edge. As a result, adjancency list should be the ideal storage paradigm.


### 1.3 Distance Matrix

#### 1.3.1

I again implemented the `getDistanceMatrix` method in the `GraphBase` class (found in `/include/graph_base.h`). This method calls `BFS` on each vertex in the graph, which populates the `_distance` attribute of each vertex, which is then extracted into the square distance matrix.

This provides me a great way to compare side to side the hypothesis put forth in answer 1.2.2 that the adjacency list should in theory be faster than the adjacency matrix.

#### 1.3.2
 
See 1.4

## 1.4 Algorithmic Analysis


THIS IS IMPORTANT DO LAST

