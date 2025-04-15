# Graph Implementation with Dijkstra's Algorithm

This project implements an undirected weighted graph data structure with Dijkstra's shortest path algorithm. It was developed as part of the COP 4530 course assignment.

## Features

- Graph implementation using only STL `vector` and `string`
- Undirected weighted graph representation
- Dijkstra's shortest path algorithm implementation
- Vertex and edge management (add/remove)
- Comprehensive test cases

## Project Structure

- `Graph.hpp` - Graph class header file
- `Graph.cpp` - Graph class implementation
- `GraphBase.hpp` - Abstract base class definition
- `main.cpp` - Test program and examples

## Building the Project

To compile the project, use:

```bash
g++ -std=c++11 -Wall -Wextra main.cpp Graph.cpp -o graph_test
```

## Running Tests

The project includes several test cases:
1. Example graph from the assignment
2. Additional test graph
3. Edge cases (empty graph, single vertex, etc.)
4. Vertex operations (add/remove vertices and edges)

To run the tests:

```bash
./graph_test
```

## Implementation Details

- Uses adjacency list representation with vectors
- Implements Dijkstra's algorithm without priority queue
- Handles edge cases and invalid inputs gracefully
- Time complexity: O(V²) for shortest path calculation

## Author

[Your Name]
COP 4530 - Data Structures 