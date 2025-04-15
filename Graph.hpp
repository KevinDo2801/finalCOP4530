#ifndef GRAPH_H
#define GRAPH_H

#include "GraphBase.hpp"
#include <string>
#include <vector>

// Implement the Graph class that inherits from GraphBase.
// Use an adjacency list stored as an unordered_map from label to list of edges.
// Each edge should be a struct with destination label and weight.

class Graph : public GraphBase {
public:
    Graph();
    ~Graph();

    void addVertex(std::string label) override;
    void removeVertex(std::string label) override;
    void addEdge(std::string label1, std::string label2, unsigned long weight) override;
    void removeEdge(std::string label1, std::string label2) override;
    unsigned long shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path) override;

private:
    struct Edge {
        std::string to;
        unsigned long weight;
    };

    struct Vertex {
        std::string label;
        std::vector<Edge> edges;
    };

    // Helper functions for our vector-based implementation
    int findVertexIndex(const std::string& label) const;
    void removeEdgeFromVertex(int vertexIndex, const std::string& targetLabel);
    
    std::vector<Vertex> vertices;  // Replaces unordered_map and list
};

#endif 