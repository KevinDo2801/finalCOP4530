#include "Graph.hpp"
#include <algorithm>
#include <queue>
#include <limits>

Graph::Graph() {
    // Initialize an empty graph
}

Graph::~Graph() {
    // Clear all vertices and edges
    adjList.clear();
}

void Graph::addVertex(std::string label) {
    // If the label does not exist in adjList, insert it with an empty list
    if (adjList.find(label) == adjList.end()) {
        adjList[label] = std::list<Edge>();
    }
}

void Graph::removeVertex(std::string label) {
    // Remove the vertex and all its associated edges from the graph
    if (adjList.find(label) != adjList.end()) {
        // Remove all edges pointing to this vertex
        for (auto& pair : adjList) {
            pair.second.remove_if([&label](const Edge& edge) {
                return edge.to == label;
            });
        }
        // Remove the vertex itself
        adjList.erase(label);
    }
}

void Graph::addEdge(std::string label1, std::string label2, unsigned long weight) {
    // Add an undirected edge between label1 and label2 with given weight
    // Do nothing if either label doesn't exist or if it's a self-loop
    if (label1 == label2) return; // No self-loops allowed
    
    // Check if both vertices exist
    if (adjList.find(label1) != adjList.end() && adjList.find(label2) != adjList.end()) {
        // Add edge from label1 to label2
        adjList[label1].push_back({label2, weight});
        // Add edge from label2 to label1 (undirected graph)
        adjList[label2].push_back({label1, weight});
    }
}

void Graph::removeEdge(std::string label1, std::string label2) {
    // Remove the edge from both label1 and label2's adjacency lists
    if (adjList.find(label1) != adjList.end() && adjList.find(label2) != adjList.end()) {
        // Remove edge from label1 to label2
        adjList[label1].remove_if([&label2](const Edge& edge) {
            return edge.to == label2;
        });
        // Remove edge from label2 to label1 (undirected graph)
        adjList[label2].remove_if([&label1](const Edge& edge) {
            return edge.to == label1;
        });
    }
}

unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path) {
    // Check if start and end vertices exist
    if (adjList.find(startLabel) == adjList.end() || adjList.find(endLabel) == adjList.end()) {
        return 0;
    }

    // Priority queue for Dijkstra's algorithm
    using QueueElement = std::pair<unsigned long, std::string>;
    std::priority_queue<QueueElement, std::vector<QueueElement>, std::greater<QueueElement>> pq;
    
    // Distance map and previous vertex map
    std::unordered_map<std::string, unsigned long> distances;
    std::unordered_map<std::string, std::string> previous;
    
    // Initialize distances
    for (const auto& pair : adjList) {
        distances[pair.first] = std::numeric_limits<unsigned long>::max();
    }
    distances[startLabel] = 0;
    
    // Start with the source vertex
    pq.push({0, startLabel});
    
    while (!pq.empty()) {
        auto current = pq.top();
        pq.pop();
        
        std::string currentLabel = current.second;
        unsigned long currentDist = current.first;
        
        // If we've reached the end vertex, we can stop
        if (currentLabel == endLabel) {
            break;
        }
        
        // If we've already found a better path to this vertex, skip it
        if (currentDist > distances[currentLabel]) {
            continue;
        }
        
        // Check all neighbors
        for (const auto& edge : adjList[currentLabel]) {
            unsigned long newDist = currentDist + edge.weight;
            if (newDist < distances[edge.to]) {
                distances[edge.to] = newDist;
                previous[edge.to] = currentLabel;
                pq.push({newDist, edge.to});
            }
        }
    }
    
    // If we couldn't reach the end vertex
    if (distances[endLabel] == std::numeric_limits<unsigned long>::max()) {
        return 0;
    }
    
    // Reconstruct the path
    path.clear();
    std::string current = endLabel;
    while (current != startLabel) {
        path.push_back(current);
        current = previous[current];
    }
    path.push_back(startLabel);
    std::reverse(path.begin(), path.end());
    
    return distances[endLabel];
}

// ... existing code ... 