#include "Graph.hpp"
#include <iostream>

int main() {
    Graph g;

    // Add vertices
    g.addVertex("1");
    g.addVertex("2");
    g.addVertex("3");
    g.addVertex("4");
    g.addVertex("5");

    // Add edges
    g.addEdge("1", "2", 7);
    g.addEdge("1", "3", 9);
    g.addEdge("1", "5", 14);
    g.addEdge("2", "3", 10);
    g.addEdge("2", "4", 15);
    g.addEdge("3", "4", 11);
    g.addEdge("3", "5", 2);
    g.addEdge("4", "5", 6);

    std::vector<std::string> path;
    unsigned long cost = g.shortestPath("1", "5", path);

    std::cout << "Shortest distance: " << cost << std::endl;
    std::cout << "Path: ";
    for (const auto &label : path) {
        std::cout << label << " ";
    }
    std::cout << std::endl;

    return 0;
} 