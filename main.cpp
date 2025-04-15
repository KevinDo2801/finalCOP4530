#include "Graph.hpp"
#include <iostream>
#include <cassert>

void testGraph1() {
    std::cout << "\nTesting Graph 1 (Example from assignment):" << std::endl;
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

    // Test shortest path from 1 to 5
    std::vector<std::string> path;
    unsigned long cost = g.shortestPath("1", "5", path);
    
    std::cout << "Path from 1 to 5:" << std::endl;
    std::cout << "Cost: " << cost << std::endl;
    std::cout << "Path: ";
    for (const auto& vertex : path) {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;
    
    // Expected cost should be 11 (1->3->5)
    assert(cost == 11);
}

void testGraph2() {
    std::cout << "\nTesting Graph 2:" << std::endl;
    Graph g;
    
    // Add vertices
    g.addVertex("A");
    g.addVertex("B");
    g.addVertex("C");
    g.addVertex("D");
    g.addVertex("E");

    // Add edges
    g.addEdge("A", "B", 4);
    g.addEdge("A", "C", 2);
    g.addEdge("B", "C", 1);
    g.addEdge("B", "D", 5);
    g.addEdge("C", "D", 8);
    g.addEdge("C", "E", 10);
    g.addEdge("D", "E", 2);

    // Test shortest path from A to E
    std::vector<std::string> path;
    unsigned long cost = g.shortestPath("A", "E", path);
    
    std::cout << "Path from A to E:" << std::endl;
    std::cout << "Cost: " << cost << std::endl;
    std::cout << "Path: ";
    for (const auto& vertex : path) {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;
}

void testEdgeCases() {
    std::cout << "\nTesting Edge Cases:" << std::endl;
    Graph g;
    std::vector<std::string> path;
    
    // Test 1: Empty graph
    std::cout << "Testing empty graph..." << std::endl;
    assert(g.shortestPath("A", "B", path) == 0);
    assert(path.empty());
    
    // Test 2: Single vertex
    std::cout << "Testing single vertex..." << std::endl;
    g.addVertex("A");
    assert(g.shortestPath("A", "A", path) == 0);
    
    // Test 3: Two vertices without edge
    std::cout << "Testing disconnected vertices..." << std::endl;
    g.addVertex("B");
    assert(g.shortestPath("A", "B", path) == 0);
    
    // Test 4: Remove vertex and its edges
    std::cout << "Testing vertex removal..." << std::endl;
    g.addEdge("A", "B", 5);
    g.removeVertex("A");
    assert(g.shortestPath("A", "B", path) == 0);
    
    std::cout << "All edge cases passed!" << std::endl;
}

void testVertexOperations() {
    std::cout << "\nTesting Vertex Operations:" << std::endl;
    Graph g;
    
    // Test adding vertices
    g.addVertex("A");
    g.addVertex("B");
    g.addVertex("C");
    
    // Test adding duplicate vertex
    g.addVertex("A");  // Should not create duplicate
    
    // Test removing vertex
    g.removeVertex("B");
    
    // Test removing non-existent vertex
    g.removeVertex("X");  // Should handle gracefully
    
    // Test adding and removing edges
    g.addEdge("A", "C", 5);
    g.removeEdge("A", "C");
    g.removeEdge("A", "X");  // Should handle non-existent edge gracefully
    
    std::cout << "Vertex operations completed successfully!" << std::endl;
}

int main() {
    try {
        std::cout << "Starting Graph Tests..." << std::endl;
        
        testGraph1();
        testGraph2();
        testEdgeCases();
        testVertexOperations();
        
        std::cout << "\nAll tests completed successfully!" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
} 